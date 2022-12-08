#include <WiFi.h>
#include <PubSubClient.h>
#include "arduino_secrets.h"
#include <ESP32AnalogRead.h>
#include <ESP32_Servo.h>
#include <cstring>

// Video code
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
// ------

// WiFi details
const char* ssid = SECRET_SSID;
const char* pass = SECRET_PASS;
WiFiClient wifiClient;

// Servo
int servoPin = 32;
Servo servo;
int angle = 0;

// PubSubClient
const char* mqttServer = MQTT_SERVER;
const char* mqttUser = MQTT_USER;
const char* mqttPass = MQTT_PASS;
PubSubClient client(wifiClient);
char message[4];

// Callback values
int internalLight = -1;
int externalLight = -1;
int movement = 0;

void setup() {
  // Create serial
  Serial.begin(115200);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  display.display();
  delay(2000); // Pause for 2 seconds

  // Clear the buffer
  display.clearDisplay();

  // Draw a single pixel in white
  display.drawPixel(10, 10, SSD1306_WHITE);

  // Show the display buffer on the screen. You MUST call display() after
  // drawing commands to make them visible on screen!
  display.display();
  delay(2000);

  // Servo setup
  servo.attach(servoPin);
  servo.write(angle);

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
  delay(50);
  client.loop();
  // Logic and OLED and servo
  renderValues();
}

void connectToMqtt(){
  while(!client.connected()){
    String clientId = "LightSense_Monitor";
    if (client.connect(clientId.c_str(), mqttUser, mqttPass)){
      client.subscribe("home/room/bedroom/light");
      client.subscribe("home/external/light");
    }
  }
}

void mqttReader(char* topic, byte* payload, unsigned int length){
  // Get values by converting bytes
  Serial.println("hello");
  if (topic == "home/room/bedroom/light"){
    //Serial.println((char)payload[0]);
  }
  else if (topic == "home/external/light"){
    //Serial.println((char)payload[0]);
  }
}

void renderValues(void) {
  display.clearDisplay();
  delay(250);
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(10, 0);
  if (internalLight > externalLight){
    display.println("HAPPY :)");
  }
 else{
   display.println("SAD :(");
 }
  display.display();
}