#include <Wire.h>
#include "config.h"
#include "bt.h"

#define bt_led 2

//Bluetooth Task
TaskHandle_t ComCtrl;
//IO task
TaskHandle_t IoCtrl;

String transmitOrder(int DID, byte orderType, byte orderParam)
{
  Wire.begin();

  Wire.beginTransmission(DID);
  Wire.write('c');
  Wire.write(orderType);
  Wire.write('p')
  Wire.write(orderParam);
  Wire.write('e')
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

  loadConfig("MRBR");
  loadConfig("MRSR_S1");
  loadConfig("MRSR_S2");
}

void IoTask (void * pvParameters){
  while(true){
    switch(btState){
      case STANDBY:
        while(btState == STANDBY){
          digitalWrite(bt_led, HIGH);
          delay(200);
          digitalWrite(bt_led, LOW);
          delay(200);
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
  Serial1.begin(115200, SERIAL_8N1, 19, 18);
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
        Serial.println(" ////COMMAND LIST\\\\");
        Serial.println(" show {parameter} : Will shows informations.");
        Serial.println("       parameters:\n");
        Serial.println("       route [-r] : Will displays all the existing route included in the config.json file.");
        Serial.println("       address [-a] : Will displays the current I2C address of the MRBR.");
        Serial.println("");
        Serial.println(" help [-h] : Will shows this help message");
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
        Serial.print("MRBR I2C address : 0x01");
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
