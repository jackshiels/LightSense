#include <WiFi.h>
#include <PubSubClient.h>
#include "arduino_secrets.h"

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

// Light sensor variables
int lightPin = 34;
int lightVal = 0;
float percentVal = 0.0;
char lightCharVal[30];

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
  pinMode(lightPin, INPUT);

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

  // Loop
  client.loop();
}

void loop() {
  delay(2500);
  
  // Light
  percentVal = analogRead(lightPin);
  lightVal = (percentVal / 4095) * 100;
  Serial.println(lightVal);
  snprintf(lightCharVal, 5, "%d%", lightVal);

  // MQTT
  client.publish("home/external/light", lightCharVal);

  // OLED
  renderValues();
}

void connectToMqtt(){
  while(!client.connected()){
    String clientId = "LightSensor_External";
    if (client.connect(clientId.c_str(), mqttUser, mqttPass)){
      client.subscribe("home/external");
    }
  }
}

void renderValues(void) {
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(10, 0);
  snprintf(lightCharVal, 30, "L: %d%%", lightVal);
  display.println(lightCharVal);
  display.display();
}