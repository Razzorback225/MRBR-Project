/*
  This is the firmware for MRBR - Standalone Node
  This firmware is designed to be use on MRBR-Nodes
  without the usage of the Nuclueus (Only the Nodes
  and A-Nodes).

  The Master Node and its peripherals are 
  interconnected via an I2C bus.
  Up to 126 devices could be configured on the bus
  as 2 addresses are reserved :
  - Address 0 is the address of the master,
  - Address 127 is the broadcast address use by
  the peripherals to ask to the master for an 
  address.
*/

#include <BluetoothSerial.h>
#include <AudioTools.h>
#include <ArduinoJson.h>

#define HW_VERSION "1.0.0"
#define SW_VERSION "2.0.0"
#define HW_TYPE "MRBR-(SN)"

BluetoothSerial bts;
I2SStream i2s0;
I2SStream i2s1;
VolumeStream volume0(i2s0);
VolumeStream volume1(i2s1);
SineWaveGenerator<int32_t> sineWave(32000);            
GeneratedSoundStream<int32_t> sound(sineWave);
StreamCopy copier0(volume0, sound);
StreamCopy copier1(volume1, sound);

bool isBtConnected = false;
float tracksSpeeds[4] = {0.0,0.0,0.0,0.0};

void btsCallback(esp_spp_cb_event_t event, esp_spp_cb_param_t *param){
  switch(event){
    //On data received
    case ESP_SPP_DATA_IND_EVT:
      if(bts.available() > 0){
        String rawCmd = bts.readStringUntil('\n');

        decodeCommand(rawCmd);
      }
      break;
    //On connection opened 
    case ESP_SPP_SRV_OPEN_EVT:
      isBtConnected = true;
      Serial.println("{'wtd' : {'msg':'Bluetooth client connected.','code':0x01}}");
      break;
    //On connection closed
    case ESP_SPP_SRV_STOP_EVT:
      isBtConnected = false;
      Serial.println("{'wtd' : {'msg':'Bluetooth client disconnected.','code':0x00}}");
      break;
  }
}

void decodeCommand(String rawCommand){
  DynamicJsonDocument cmdJson(256);

  DeserializationError err = deserializeJson(cmdJson, rawCommand);
  switch(err.code()){
    case DeserializationError::Ok:
      if(cmdJson.containsKey("tr")){
        int trackId = cmdJson["tr"][0];
        float trackSpeed = cmdJson["tr"][1].as<float>();
        bool reverseDir = cmdJson["tr"][2].as<bool>();

        //If user ask to activate reverse solenoide
        if(reverseDir){
          // If the track speed is not null, decrease the speed before changing direction.
          if(tracksSpeeds[trackId] > 0.0){
            //If track to control is on channel 0 or 1
            while(tracksSpeeds[trackId] > 0.0){
              tracksSpeeds[trackId] -= 0.1;
              StaticJsonDocument<256> responseJson;
              JsonArray trackData = responseJson.createNestedArray("tr");
              trackData.add(trackId);
              trackData.add(tracksSpeeds[trackId]);
              serializeJson(responseJson, Serial);
              if(isBtConnected){
                serializeJson(responseJson, bts);
              }
              if(trackId < 2){
                float volume = (2/3) * tracksSpeeds[trackId];
                volume0.setVolume(volume, trackId);
                delay(250);
              }
              else{
                float volume = (2/3) * tracksSpeeds[trackId];
                volume1.setVolume(volume, trackId - 2);
                delay(250);
              }
            }
          }
          // Switch direction
          if(trackId < 2){
            volume0.setVolume(1.0, trackId);
            delay(500);
            volume0.setVolume(0.0, trackId);
          }
          else{
            volume1.setVolume(1.0, trackId - 2);
            delay(500);
            volume1.setVolume(0.0, trackId - 2);
          }

        }
        else{
          if(trackSpeed <= 1.0){
            tracksSpeeds[trackId] = trackSpeed;
            StaticJsonDocument<256> responseJson;
            JsonArray trackData = responseJson.createNestedArray("tr");
            trackData.add(trackId);
            trackData.add(tracksSpeeds[trackId]);
            serializeJson(responseJson, Serial);
            if(isBtConnected){
              serializeJson(responseJson, bts);
            }
            if(trackId < 2){
              float volume = (2/3) * tracksSpeeds[trackId];
              volume0.setVolume(volume, trackId);
            }
            else{
              float volume = (2/3) * tracksSpeeds[trackId];
              volume1.setVolume(volume, trackId - 2);
            }
          }
          else{

          }
        }
      }
      else if(cmdJson.containsKey("sw")){
        int switchId = cmdJson["sw"][0];
        int switchPos = cmdJson["sw"][1];
      }
      else if(cmdJson.containsKey("inf")){
        String filter = cmdJson["inf"];
        if(filter == "all"){
          StaticJsonDocument<256> infoJson;

          infoJson["inf"]["hw_version"] = HW_VERSION;
          infoJson["inf"]["sw_version"] = SW_VERSION;
          infoJson["inf"]["hw_type"] = HW_TYPE;

          serializeJson(infoJson, Serial); 
          if(isBtConnected){
            serializeJson(infoJson, bts);
          }
        }
      }
      break;
    case DeserializationError::InvalidInput:
      Serial.print(F("Invalid input!"));
      break;
    case DeserializationError::NoMemory:
      Serial.print(F("Not enough memory"));
      break;
    default:
      Serial.print(F("Deserialization failed"));
      break;
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  bts.register_callback(btsCallback);
  bts.begin("MRBR-Lite");


  auto config0 = i2s0.defaultConfig(TX_MODE);
  config0.pin_bck = 16;
  config0.pin_ws = 17;
  config0.pin_data = 4;
  config0.bits_per_sample = 32;
  config0.sample_rate = 48000;
  i2s0.begin(config0);  
  auto config1 = i2s1.defaultConfig(TX_MODE);
  config1.pin_bck = 16;
  config1.pin_ws = 12;
  config1.pin_data = 13;
  config1.bits_per_sample = 32;
  config1.sample_rate = 48000;
  i2s1.begin(config1);  

  sineWave.begin(2, 48000, 50.0);

  volume0.setVolume(0.0);
  volume1.setVolume(0.0);
}

void loop() {
  // put your main code here, to run repeatedly:
  copier0.copy();
  copier1.copy();

  if(Serial.available() > 0){
    String rawCommand = Serial.readStringUntil('/n');

    decodeCommand(rawCommand);
  }
}
