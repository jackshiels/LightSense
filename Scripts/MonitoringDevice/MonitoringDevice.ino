#include <WiFi.h>
#include <PubSubClient.h>
#include "arduino_secrets.h"
#include <ESP32AnalogRead.h>

// WiFi details
const char* ssid = SECRET_SSID;
const char* pass = SECRET_PASS;
WiFiClient wifiClient;

// PubSubClient
const char* mqttServer = MQTT_SERVER;
const char* mqttUser = MQTT_USER;
const char* mqttPass = MQTT_PASS;
PubSubClient client(wifiClient);

// Callback values
int internalLight = 0;
int externalLight = 0;
int movement = 0;

void setup() {
  // Create serial
  Serial.begin(115200);

  // WiFi connect
  WiFi.begin(ssid, pass);
  Serial.print("Connecting");
  while(WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(1000);
  }
  Serial.println("Connected to WiFi");

  // PubSubClient
  client.setServer(mqttServer, 1883);
  if (!client.connected()){
    connectToMqtt();
  }
  client.setCallback(mqttReader);
}

void loop() {
  delay(1000);
  
  // Logic and OLED
  // TBD
}

void connectToMqtt(){
  while(!client.connected()){
    String clientId = "LightSensor_External";
    if (client.connect(clientId.c_str(), mqttUser, mqttPass)){
      client.subscribe("home/external");
    }
  }
}

void mqttReader(char* topic, byte* payload, unsigned int length){
  // Get values
}