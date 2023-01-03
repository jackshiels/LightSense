#include <WiFi.h>
#include <PubSubClient.h>
#include "arduino_secrets.h"

// OLED code. All OLED code modified from https://github.com/adafruit/Adafruit_SSD1306
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32

#define OLED_RESET     -1
#define SCREEN_ADDRESS 0x3C
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
  // Set up the PIR pin
  pinMode(lightPin, INPUT);

  // Create serial bus
  Serial.begin(115200);

  // Set up the screen for rendering the light value
  prepareScreen();

  // Connect to WiFi
  WiFi.begin(ssid, pass);
  Serial.print("Connecting");
  while(WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(1000);
  }
  Serial.println("Connected to WiFi");

  // Connect to the local MQTT server
  client.setServer(mqttServer, 1883);
  if (!client.connected()){
    connectToMqtt();
  }

  // Loop the MQTT client to send/receive
  client.loop();
}

void loop() {
  delay(2500);
  
  // Get the light value
  percentVal = analogRead(lightPin);
  // Convert the 12-bit value into a percentage
  lightVal = (percentVal / 4095) * 100;
  Serial.println(lightVal);
  // Construct a string for the OLED display and MQTT server
  snprintf(lightCharVal, 5, "%d%", lightVal);

  // Publish the light value to MQTT server
  client.publish("home/external/light", lightCharVal);

  // Render the value to OLED
  renderValues();
}

// Repeatedly attempt to connect to MQTT server. Code modified from 
// https://workshops.cetools.org/codelabs/CASA0014-2-Plant-Monitor/
void connectToMqtt(){
  while(!client.connected()){
    String clientId = "LightSensor_External";
    if (client.connect(clientId.c_str(), mqttUser, mqttPass)){
      client.subscribe("home/external");
    }
  }
}

// Render the light values on the OLED
void renderValues(void) {
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(10, 0);
  snprintf(lightCharVal, 30, "L: %d%%", lightVal);
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