#include "BluetoothSerial.h"
#include <Wire.h>
#include "SPIFFS.h"
#include <ArduinoJson.h>

#define RTR_ADD 0x01
#define bt_led 2
#define DEVICE_TYPE "MRBR"

#define STANDBY 1
#define CONNECTED 2

#define VERSION "1.0"

//Bluetooth Task
TaskHandle_t ComCtrl;
//IO task
TaskHandle_t IoCtrl;

BluetoothSerial BT;

int btState;

struct Slave{
  byte DID;
  const char* Name;
};
struct Routes {
  byte NID;
  const char* interface;
  Slave slave[127];
  int slaveCount;
};

Routes MRBR;
Routes MRSR_S1;
Routes MRSR_S2;

void bt_callback(esp_spp_cb_event_t event, esp_spp_cb_param_t *param){
  switch(event)
  {
    case ESP_SPP_SRV_OPEN_EVT:
      btState = CONNECTED;
      break;
    case ESP_SPP_CLOSE_EVT:
      btState = STANDBY;
      break;
  }
}

void loadRoute(String Network)
{
      //Print Routing Table
    File routeFile = SPIFFS.open("/route.json", "r");

    StaticJsonDocument<1024> routeDoc;
            
    DeserializationError error = deserializeJson(routeDoc, routeFile);
    if(error)
    {
        Serial.println("Failed to load JSON");
        Serial.print("Error: ");Serial.println(error.c_str());
    }
    else
    {
      byte NID = routeDoc[Network]["MRBR_NID"];
      const char* INT = routeDoc[Network]["Interface"];
      Slave slaves[127];
      for(int slaveInd = 0; slaveInd < routeDoc[Network]["slaves"].size(); slaveInd++)
      {
          Slave slave;
          slave.DID = routeDoc[Network]["slaves"][slaveInd]["DID"];
          slave.Name = routeDoc[Network]["slaves"][slaveInd]["NAME"];
          slaves[slaveInd] = slave;   
      }
      int slaveCount = routeDoc[Network]["slaves"].size();

      routeFile.close();

      if(Network == "MRBR")
      {
        MRBR.NID = NID;
        MRBR.interface = INT; 
        for(int i = 0; i < slaveCount; i++)
        {
          MRBR.slave[i] = slaves[i];          
        }
        MRBR.slaveCount = slaveCount;                
      }
      else if(Network == "MRSR_S1")
      {
        MRSR_S1.NID = NID;
        MRSR_S1.interface = INT;
        for(int i = 0; i < slaveCount; i++)
        {
          MRSR_S1.slave[i] = slaves[i];
        }  
        MRSR_S1.slaveCount = slaveCount;                         
      }
      else if(Network == "MRSR_S2")
      {
        MRSR_S2.NID = NID;
        MRSR_S2.interface = INT;
        for(int i = 0; i < slaveCount; i++)
        {
          MRSR_S2.slave[i] = slaves[i];
        }  
        MRSR_S2.slaveCount = slaveCount;                         
      }
    }
}

void printRoute(Routes route)
{
      int d1, d2, i1, i2;

      for(int slaveInd = 0; slaveInd < route.slaveCount; slaveInd++)
      {
          Serial.println("|------------|--------------------|------------|");      
          Serial.print  ("|    ");Serial.print("0x");
          if(route.slave[slaveInd].DID < 10)
          {
            Serial.print("0");
          }
          Serial.print(route.slave[slaveInd].DID, HEX);
          Serial.print("    |");
          if(strlen(route.slave[slaveInd].Name)%2 == 0)
          {
            int delta = 20 - strlen(route.slave[slaveInd].Name);
            d1, d2 = delta/2;
          }
          else{
            int delta = 20 - strlen(route.slave[slaveInd].Name);
            d1 = delta/2;
            d2 = d1 + 1;
          }
          
          for(i1=0; i1<d1; i1++)
          {
            Serial.print(" ");
          }
  
          Serial.print(route.slave[slaveInd].Name);
  
          for(i2=0; i2<d2; i2++)
          {
            Serial.print(" ");
          }
          Serial.print("|");
          Serial.print("     ");Serial.print(route.interface);Serial.println("     |");       
  
      }
      Serial.println("________________________________________________");
}

String transmitOrder(int DID, byte orderType, byte orderParam)
{
  Wire.begin();

  Wire.beginTransmission(DID);
  Wire.write(orderType);
  Wire.write(orderParam);
  Wire.endTransmission();

  Wire.requestFrom(DID, 6);
  String ret;
  while(Wire.available()){
    ret += Wire.read();
  }

  if(ret == "OK")
  {
    return "OK";
  }
  else{
    return "NOK";
  }
}

void setup() {

  xTaskCreatePinnedToCore(ComTask, "Bluetooth", 10000, NULL, 1, &ComCtrl,0);
  delay(500);
  xTaskCreatePinnedToCore(IoTask, "IO", 10000, NULL, 1, &IoCtrl,1);
  delay(500);

  loadRoute("MRBR");
  loadRoute("MRSR_S1");
  loadRoute("MRSR_S2");
}

void IoTask (void * pvParameters){
  while(true){
    switch(btState){
      case STANDBY:
        while(btState == STANDBY){
          digitalWrite(bt_led, HIGH);
          delay(250);
          digitalWrite(bt_led, LOW);
          delay(250);
        }
        break;
      case CONNECTED:
        digitalWrite(bt_led, HIGH);
        break;
    }
  }
}
//Pass command received via bluetooth to correct slave
//Identify if slave is in its I2C network,
//
//If it is, MRBR send the command to the slave via I2C
//
//If it is not, MRBR send the command via UART to the right sub-router [MRSR]
//(according to the network ID [NID]). To achieve this, the MRBR reads its routing table JSON
//to find to which UART the command has to be send
//
void ComTask (void * pvParameters){

  BT.begin("MRBR");
  BT.register_callback(bt_callback);
  pinMode(bt_led, OUTPUT);

  btState = STANDBY;

  Serial.begin(115200);
  Serial1.begin(115200);
  Serial2.begin(115200);

  if(!SPIFFS.begin(true)){
    Serial.println("E/FS/M#");
  }

  while(true){
    if(Serial.available()>0)
    {

      String cmd = Serial.readStringUntil('#');

      //If the string received is a user command
      if(cmd == "help" || cmd == "-h")
      {
        Serial.println("# ////COMMAND LIST\\\\");
        Serial.println("# show {parameter} : Will shows informations.");
        Serial.println("#       parameters:\n#");
        Serial.println("#       route [-r] : Will displays all the existing route included in the config.json file.");
        Serial.println("#       address [-a] : Will displays the current I2C address of the MRBR.");
        Serial.println("#");
        Serial.println("# help [-h] : Will shows this help message");
      }
      else if(cmd == "show route" || cmd == "show -r")
      {
        Serial.println("________________________________________________");
        Serial.println("|                 MRBR NETWORK                 |");
        Serial.println("|----------------------------------------------|");
        Serial.println("|     DID    |       NAME         |  MRBR INT  |");
        printRoute(MRBR);
  
        Serial.println("________________________________________________");
        Serial.println("|                 MRSR_S1 NETWORK              |");
        Serial.println("|----------------------------------------------|");
        Serial.println("|     DID    |       NAME         |  MRBR INT  |");
        printRoute(MRSR_S1);
        
        Serial.println("________________________________________________");
        Serial.println("|                 MRSR_S2 NETWORK              |");
        Serial.println("|----------------------------------------------|");
        Serial.println("|     DID    |       NAME         |  MRBR INT  |");           
        printRoute(MRSR_S2);     
                   
      }
      else if(cmd == "show address" || cmd == "show -a")
      {
        Serial.print("MRBR I2C address : 0x0");
        Serial.println(RTR_ADD, HEX);
      }
      else
      {
        //Serial.println(cmd);
      }
    }
    else if(BT.available()>0)
    {
      byte NID = BT.readStringUntil('/').toInt();
      int DID = BT.readStringUntil('/').toInt();
      byte orderType = BT.readStringUntil('/').toInt();
      byte orderParam = BT.readStringUntil('#').toInt();
      
      if(NID == MRBR.NID)
      {
        BT.print(transmitOrder(DID, orderType, orderParam));BT.println('#');
      }
      else if(NID == MRSR_S1.NID){
        Serial1.println("DEBUG : MRSR_S1");
        if(DID < 10){Serial.print('0');}Serial.print(DID);Serial.print('/');if(orderType < 10){Serial.print('0');}Serial.print(orderType);Serial.print('/');if(orderParam < 10){Serial.print('0');}Serial.print(orderParam);Serial.println('#');
      }
      else if(NID == MRSR_S2.NID){
        Serial2.println("DEBUG : MRSR_S2");
        if(DID < 10){Serial.print('0');}Serial.print(DID);Serial.print('/');if(orderType < 10){Serial.print('0');}Serial.print(orderType);Serial.print('/');if(orderParam < 10){Serial.print('0');}Serial.print(orderParam);Serial.println('#');
      }
      else{
        Serial.println("Default :");
        if(DID < 10){Serial.print('0');}Serial.print(DID);Serial.print('/');if(orderType < 10){Serial.print('0');}Serial.print(orderType);Serial.print('/');if(orderParam < 10){Serial.print('0');}Serial.print(orderParam);Serial.println('#');
      }
    }
    delay(2);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(5);
}
