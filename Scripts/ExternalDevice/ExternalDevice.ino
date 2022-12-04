#include <WiFi.h>
#include <PubSubClient.h>
#include "arduino_secrets.h"
#include <ESP32AnalogRead.h>

// Light sensor variables
int lightPin = 32;
int lightVal = 0;
char lightCharVal[5];

ESP32AnalogRead adc;

// WiFi details
const char* ssid = SECRET_SSID;
const char* pass = SECRET_PASS;
WiFiClient wifiClient;

// PubSubClient
const char* mqttServer = MQTT_SERVER;
const char* mqttUser = MQTT_USER;
const char* mqttPass = MQTT_PASS;
PubSubClient client(wifiClient);

void setup() {
  // Set up the PIR
  //pinMode(lightPin, INPUT);
  adc.attach(32);

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
}

void loop() {
  delay(1000);
  // Light
  lightVal = adc.readVoltage();
  Serial.println(lightVal);
  snprintf(lightCharVal, 5, "%d", lightVal);

  // MQTT
  client.publish("home/external/light", lightCharVal);
}

void connectToMqtt(){
  while(!client.connected()){
    String clientId = "LightSensor_External";
    if (client.connect(clientId.c_str(), mqttUser, mqttPass)){
      client.subscribe("home/external");
    }
  }
}
