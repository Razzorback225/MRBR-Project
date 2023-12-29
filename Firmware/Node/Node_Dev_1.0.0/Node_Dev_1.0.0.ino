#include <Arduino.h>
#include <SPI.h>
#include <ETH.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <Adafruit_MCP23X17.h>
#include <Wire.h>

#define CONFIG_ETH_USE_ESP32_EMAC

#define ETH_PHY_TYPE        ETH_PHY_LAN8720
#define ETH_PHY_ADDR        0
#define ETH_PHY_MDC         23
#define ETH_PHY_MDIO        18
#define ETH_PHY_POWER       5
#define ETH_CLK_MODE        ETH_CLOCK_GPIO17_OUT

#define I2C_SDA 33
#define I2C_SCL 32

#define I2S0_WS 15
#define I2S0_DOUT 16
#define I2S_SCL 14
#define I2S1_WS 12
#define I2S1_DOUT 13

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] \n");
  String buffer = "";
  for (int i=0;i<length;i++) {
    buffer += (char)payload[i];
  }
  printf("Raw buffer : %s", buffer.c_str());
  DynamicJsonDocument payloadJson(1024);
  DeserializationError err = deserializeJson(payloadJson, buffer);
  switch (err.code()) {
      case DeserializationError::Ok:
          if(payloadJson.containsKey("tr")){
            int trackId = payloadJson["tr"][0];
            float trackSpeed = payloadJson["tr"][1];
            bool reverseDir = payloadJson["tr"][2];

            if(reverseDir){
              trackSpeed = 0.0;

              // Switch direction
            }
          }
          else if(payloadJson.containsKey("sw")){
            int switchId = payloadJson["sw"][0];
            int switchPos = payloadJson["sw"][1];
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

static bool eth_connected = false;
String hostname = "Node-";

String getSerial(){
  uint32_t chipId = 0;

	for(int i=0; i<17; i=i+8) {
	  chipId |= ((ESP.getEfuseMac() >> (40 - i)) & 0xff) << i;
	}

  return String(chipId);
}

void WiFiEvent(WiFiEvent_t event)
{

  switch (event) {
    case ARDUINO_EVENT_ETH_START:
      Serial.println("ETH Started");
      //set eth hostname here
      //ETH.setHostname(hostname.c_str());
      break;
    case ARDUINO_EVENT_ETH_CONNECTED:
      Serial.println("ETH Connected");
      break;
    case ARDUINO_EVENT_ETH_GOT_IP:
      Serial.print("ETH MAC: ");
      Serial.print(ETH.macAddress());
      Serial.print(", IPv4: ");
      Serial.print(ETH.localIP());
      if (ETH.fullDuplex()) {
        Serial.print(", FULL_DUPLEX");
      }
      Serial.print(", ");
      Serial.print(ETH.linkSpeed());
      Serial.println("Mbps");
      eth_connected = true;
      break;
    case ARDUINO_EVENT_ETH_DISCONNECTED:
      Serial.println("ETH Disconnected");
      eth_connected = false;
      break;
    case ARDUINO_EVENT_ETH_STOP:
      Serial.println("ETH Stopped");
      eth_connected = false;
      break;
    default:
      break;
  }
}


WiFiClient ethClient;
PubSubClient client(ethClient);
Adafruit_MCP23X17 io_extender;

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect(getSerial().c_str())) {
      Serial.println("connected\nSending discovery message.");
      StaticJsonDocument<200> discoveryPayload;
      discoveryPayload["node_id"] =  getSerial();
      discoveryPayload["node_address"] = ethClient.localIP();
      String payload = "";
      serializeJson(discoveryPayload, payload);
      // Pushing message on discovery topic to show presence
      client.publish("discovery",payload.c_str());
      // Subscribe to the specific node topic
      String node_topic = "nodes/" + getSerial();
      client.subscribe(node_topic.c_str());
      // Subscribe to the general node topic
      client.subscribe("nodes");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup()
{
  Serial.begin(115200);

  client.setServer("10.0.0.1", 1883);
  client.setCallback(callback);
  hostname += getSerial();
  ETH.begin();
  WiFi.onEvent(WiFiEvent);
  TwoWire i2c = TwoWire(0);
  i2c.begin(I2C_SDA, I2C_SCL, 100000);
  if(!io_extender.begin_I2C(MCP23XXX_ADDR, &i2c)){
    
  }
  // Allow the hardware to sort itself out
  delay(1500);
}

void loop()
{
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}