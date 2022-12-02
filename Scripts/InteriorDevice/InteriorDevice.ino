#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "arduino_secrets.h"

// PIR sensor variables
int PIRPin = D0;
const char* sensorVal = 0;

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
  delay(100);
  sensorVal = digitalRead(PIRPin);
  if (sensorVal == "1"){
    Serial.println("1");
  }
  else{
    Serial.println("0");
  }
  Serial.println(sensorVal);
  client.publish("home/room/bedroom", sensorVal);
}

void connectToMqtt(){
  while(!client.connected()){
    String clientId = "LightSensor_Internal";
    if (client.connect(clientId.c_str(), mqttUser, mqttPass)){
      client.subscribe("home/room/bedroom");
    }
  }
}
