#include <Wire.h>

#define S_ADD 2

//Communication Task
TaskHandle_t ComTask;
//IO Task
TaskHandle_t IoTask;

struct CmdData{
  /*Types : 
   * 0 - Switch command,
   * 1 - Track command,
   */
  int cmdType;
  int cmdParam1;
  int cmdParam2;
}

void setup() {
  xTaskCreatePinnedToCore(NetCom, "Bluetooth", 10000, NULL, 1, &ComTask,0);
  delay(500);
  xTaskCreatePinnedToCore(IOCtl, "IO", 10000, NULL, 1, &IoTask,1);
  delay(500);
}

void NetCom(void * pvParameters){
  CmdData cmdData;
  Wire.begin(S_ADD);
  Serial.begin(115200);
  String cmd;
  while(true){
    while(Wire.available()){
      cmd += Wire.read();  
    }
    if(cmd != ""){
      int pI = cmd.indexOf('p');
      int eI = cmd.indexOf('e');
      int sI = cmd.indexOf('/');
      cmdData.cmdType = cmd.substring(1,pI);
      cmdData.cmdParam1 = cmd.substring(pI + 1, sI);
      cmdData.cmdParam2 = cmd.substring(sI + 1, eI);

      Serial.print("Type : ");Serial.println(cmdData.cmdType);
      Serial.print("Param1 : "); Serial.println(cmdData.cmdParam1);
      Serial.print("Param2 : "); Serial.println(cmdData.cmdParam2);
    }
  }
}

void loop() {
  delay(5);
}
