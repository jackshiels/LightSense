#include <WiFi.h>
#include <PubSubClient.h>
#include "arduino_secrets.h"

// OLED code. All OLED code modified from https://github.com/adafruit/Adafruit_SSD1306
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

char* screenText = "";
// ------

// PIR sensor variables
int PIRPin = 34;
int sensorVal = 0;
const char* pirVal;

// Light sensor variables
int lightPin = 32;
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
int mqttPort = 1883;
PubSubClient client(wifiClient);

void setup() {
  // Set up the PIR and light pins
  pinMode(PIRPin, INPUT);
  pinMode(lightPin, INPUT);

  // Set up the OLED
  prepareDisplay();

  // Create serial bus
  Serial.begin(115200);

  // Connect to WiFi
  WiFi.begin(ssid, pass);
  Serial.print("Connecting");
  while(WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(1000);
  }
  Serial.println("Connected to WiFi");

  // Connect to the local MQTT server
  client.setServer(mqttServer, mqttPort);
  if (!client.connected()){
    connectToMqtt();
  }
}

void loop() {
  // Get motion from the PIR sensor
  delay(2500);
  sensorVal = digitalRead(PIRPin);
  if (sensorVal == 1){
    pirVal = "1";
  }
  else {
    pirVal = "0";
  }

  // Get the light value
  percentVal = analogRead(lightPin);
  // Convert the 12-bit value into a percentage
  lightVal = (percentVal / 4095) * 100;
  Serial.print("Light value is: ");
  Serial.println(lightVal);
  // Construct a string for the OLED display and MQTT
  snprintf(lightCharVal, 5, "%d", lightVal);

  // Send light and movement values to the MQTT server
  Serial.print("Movement value is: ");
  Serial.println(sensorVal);
  client.publish("home/room/bedroom/movement", pirVal);
  client.publish("home/room/bedroom/light", lightCharVal);

  // Render the light and movement values to the OLED
  renderValues();

  // Loop the MQTT client to send/receive
  client.loop();
}

// Repeatedly attempt to connect to MQTT server. Code modified from 
// https://workshops.cetools.org/codelabs/CASA0014-2-Plant-Monitor/
void connectToMqtt(){
  while(!client.connected()){
    String clientId = "LightSensor_Internal";
    if (client.connect(clientId.c_str(), mqttUser, mqttPass)){
      client.subscribe("home/room/bedroom");
    }
  }
}

// Render the light and movement values on the OLED
void renderValues(void) {
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(10, 0);
  snprintf(lightCharVal, 30, "L: %d%% \n M: %d", lightVal, sensorVal);
  display.println(lightCharVal);
  display.display();
}

// Set up the OLED for startup.
void prepareScreen(){
  display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS));
  display.display();
  delay(1000); 
  display.clearDisplay();
  delay(2000);
}