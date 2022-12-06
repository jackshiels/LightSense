#include <WiFi.h>
#include <PubSubClient.h>
#include "arduino_secrets.h"

// PIR sensor variables
int PIRPin = 34;
int sensorVal = 0;
const char* pirVal;

// Light sensor variables
int lightPin = 32;
int lightVal = 0;
char lightCharVal[5];

// WiFi details
const char* ssid = SECRET_SSID;
const char* pass = SECRET_PASS;
WiFiClient wifiClient;

// PubSubClient
const char* mqttServer = MQTT_SERVER;
const char* mqttUser = MQTT_USER;
const char* mqttPass = MQTT_PASS;
int mqttPort = 1883;
PubSubClient client(wifiClient);

void setup() {
  // Set up the PIR
  pinMode(PIRPin, INPUT);
  pinMode(lightPin, INPUT);

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
  client.setServer(mqttServer, mqttPort);
  if (!client.connected()){
    connectToMqtt();
  }
}

void loop() {
  // PIR
  delay(250);
  sensorVal = digitalRead(PIRPin);
  if (sensorVal == 1){
    pirVal = "1";
  }
  else{
    pirVal = "0";
  }

  // Light
  lightVal = analogRead(lightPin);
  Serial.println("Light value is: " + lightVal);
  snprintf(lightCharVal, 5, "%d", lightVal);

  // MQTT
  Serial.println("Movement value is: " + sensorVal);
  client.publish("home/room/bedroom/movement", pirVal);
  client.publish("home/room/bedroom/light", lightCharVal);
}

void connectToMqtt(){
  while(!client.connected()){
    String clientId = "LightSensor_Internal";
    if (client.connect(clientId.c_str(), mqttUser, mqttPass)){
      client.subscribe("home/room/bedroom");
    }
  }
}
