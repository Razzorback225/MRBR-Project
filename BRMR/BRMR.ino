#include "BluetoothSerial.h"
#include <Wire.h>
#include "SPIFFS.h"
#include <ArduinoJson.h>

#define RTR_ADD 0x01
#define bt_led 2
#define DEVICE_TYPE "MRBR"

#define STANDBY 1
#define CONNECTED 2

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
  Slave slave[];
};

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

void loadRoute(Routes route, String Network)
{
    int d1, d2, i1, i2;
      //Print Routing Table
    File routeF = SPIFFS.open("/route.json", "r");

    StaticJsonDocument<1024> routeJ;
            
    DeserializationError error = deserializeJson(routeJ, routeF);
    if(error)
    {
        Serial.println("Failed to load JSON");
        Serial.print("Error: ");Serial.println(error.c_str());
    }
    else
    {

      route.NID = routeJ[Network]["MRBR_NID"];
      route.interface = routeJ[Network]["Interface"];
  
      for(int slaveInd = 0; slaveInd < routeJ[Network]["slaves"].size(); slaveInd++)
      {
          Slave slave;
          slave.DID = routeJ[Network]["slaves"][slaveInd]["DID"];
          slave.Name = routeJ[Network]["slaves"][slaveInd]["NAME"];
          route.slave[slaveInd] = slave;
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
             
      routeF.close();
    }
}

void setup() {

  xTaskCreatePinnedToCore(ComTask, "Bluetooth", 10000, NULL, 1, &ComCtrl,0);
  delay(500);
  xTaskCreatePinnedToCore(IoTask, "IO", 10000, NULL, 1, &IoCtrl,1);
  delay(500);

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
  //Serial1.begin(115200);
  //Serial2.begin(115200);

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
        Routes MRBR;
        Routes MRSR_S1;
        Routes MRSR_S2;

        Serial.println("________________________________________________");
        Serial.println("|                 MRBR NETWORK                 |");
        Serial.println("|----------------------------------------------|");
        Serial.println("|     DID    |       NAME         |  MRBR INT  |");
        loadRoute(MRBR, "MRBR");
  
        Serial.println("________________________________________________");
        Serial.println("|                 MRSR_S1 NETWORK              |");
        Serial.println("|----------------------------------------------|");
        Serial.println("|     DID    |       NAME         |  MRBR INT  |");
        loadRoute(MRSR_S1, "MRSR_S1");
        
        Serial.println("________________________________________________");
        Serial.println("|                 MRSR_S2 NETWORK              |");
        Serial.println("|----------------------------------------------|");
        Serial.println("|     DID    |       NAME         |  MRBR INT  |");           
        loadRoute(MRSR_S2, "MRSR_S2");     
                   
      }
      else if(cmd == "show address" || cmd == "show -a")
      {
        Serial.print("MRBR I2C address : ");
        Serial.println(RTR_ADD, HEX);
      }
      else
      {
        Serial.println(cmd);
      }
    }
    else if(BT.available()>0)
    {
      //Serial.println(Serial.readString());

      String cmd = BT.readStringUntil('#');
      
    }
    delay(2);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(5);
}
