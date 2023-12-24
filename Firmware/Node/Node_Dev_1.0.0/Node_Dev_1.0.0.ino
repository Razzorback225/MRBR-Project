#include <Arduino.h>
#include <SPI.h>
#include <ETH.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

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