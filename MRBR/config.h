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

/*
 * Create 3 new "Routes" structures.
 * The first route is the route for I2C devices that are part of the MRBR's I2C network.
 * The other two are the routes for the devices in the I2C network of the 2 MRSR that could be connected via UART1 and UART2.
 */
Routes MRBR;
Routes MRSR_S1;
Routes MRSR_S2;

const char* MROS_V;

void loadConfig(String Network)
{
      //Print Routing Table
    File routeFile = SPIFFS.open("/config.json", "r");

    StaticJsonDocument<1024> routeDoc;
            
    DeserializationError error = deserializeJson(routeDoc, routeFile);
    if(error)
    {
        Serial.println("Failed to load JSON");
        Serial.print("Error: ");Serial.println(error.c_str());
    }
    else
    {
      MROS_V = routeDoc["MROS_VERSION"];
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
