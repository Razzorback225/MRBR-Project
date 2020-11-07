#include "SPIFFS.h"
#include <ArduinoJson.h>

//Slave structure 
struct Slave{
  //I2C ID of the slave device
  byte DID;
  //Name of the slave device
  const char* Name;
};
/* Route structure
 * These structures contain :
 * -The ID of the I2C network,
 * -The communication interface (S1 or S2 for serial or L for local),
 * -The slave array contains slave structures for each slaves listed in the route.json,
 * -The slaveCount variable, well..., count the amount of slaves in the array
 */
struct Routes {
  byte NID;
  const char* interface;
  Slave slave[127];
  int slaveCount;
};

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
