#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "arduino_secrets.h"

// PIR sensor variables
int PIRPin = D0;
int sensorVal = 0;
const char* pirVal;

// Light sensor variables
int lightPin = A0;
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
  client.setServer(mqttServer, 1883);
  if (!client.connected()){
    connectToMqtt();
  }
}

void loop() {
  // PIR
  delay(1000);
  sensorVal = digitalRead(PIRPin);
  if (sensorVal == 1){
    Serial.println("1");
    pirVal = "1";
  }
  else{
    Serial.println("0");
    pirVal = "0";
  }

  // Light
  lightVal = analogRead(lightPin);
  Serial.println(lightVal);
  snprintf(lightCharVal, 5, "%d", lightVal);

  // MQTT
  Serial.println(sensorVal);
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
