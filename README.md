# LightSense
<b>Jack Shiels</b>
A project for UCL's CASA0016 module for building connected environments

Video available here: https://youtu.be/dj-cJYu9SqU

# Problem - Energy Costs £££'s!
The advent of the Russia-Ukraine war created an unstable energy market, leading to some serious costs for the average Briton [[1]](#1). As such, many will seek to minimise their energy costs as Winter approaches. The Internet of Things (IoT) could help to mend this situation through careful energy management and social conditioning to prevent wastage. The aim of this project is to remind individuals to monitor their energy usage when it comes to indoor lighting.

# Solution: LightSense Light Monitoring and Presentation
Energy can take many forms - heat, light, sound, and many more. However, what's the use of energy if it is not being enjoyed by the user? 

LightSense is a family of small sensor units with a specific purpose - to track light and temperature levels in rooms, correlate them with human occupation of those rooms, and recommend the user adjusts their energy usage when room energy is being wasted. For example, a room may be left with the lights on, but nobody is there. This is a waste! Similarly, a window may be left open, leading to an unacceptable drop in temperature when the user arrives home. In this case, valuable heat energy is lost. Preventative alerts allow both situations to be avoided or mitigated. 

This system would be split into three sensors:
- An external light monitor
- An internal light and motion monitor
- A reporting device to indicate energy usage

The original sketch for my design is shown below:

![Architecture diagram](https://github.com/jackshiels/LightSense/blob/main/Images/Sketchup.jpg?raw=true)

## Early Prototypes

Originally, I intended to include a Unity-based home monitor that would illustrate how my home was being lit. However, I quickly realised that this would be too challenging in the time-frame. I instead elected to create a device that would reflect the state of the system. A couple of early prototypes were built. At first, I just fooled around with breadboards and Arduinos:

![Breadboard](https://github.com/jackshiels/LightSense/blob/main/Images/Breadboard.jpeg?raw=true)

Afterwards, I designed several Fritz diagrams from which to create a more concrete design. Each of the individual sensors is illustrated and described:
- The external sensor only picks up external light and displays the light level of a light sensor as a percentage on a small OLED screen.
- The internal sensor uses a light sensor and a PIR sensor to track internal light and movement.
- The monitor only uses an OLED display to indicate if energy is being wasted.

![Fritz](https://github.com/jackshiels/LightSense/blob/main/Images/Fritz.jpg?raw=true)

I also ordered several parts from Amazon and eBay. These included:

- Three ESP32 modules.
- Several resistor-based light sensors.
- Several SSD1306 OLED displays.

## Construction

I employed a rapid prototyping approach using architectural foam and glue to build sensors in a short period:

![Fritz](https://github.com/jackshiels/LightSense/blob/main/Images/PrototypeBox.jpeg?raw=true)

However, these designs were quite flimsy. I realised that I needed a more robust prototyping approach. So, instead of foam I bought a lego set from which to design my enclosures.:

![Lego](https://github.com/jackshiels/LightSense/blob/main/Images/Lego.jpeg?raw=true)

I also decided to solder the screen and light sensor onto a PCB for the external sensor. There were some casualties along the way!

![Soldering](https://github.com/jackshiels/LightSense/blob/main/Images/Solder.jpeg?raw=true)

My efforts quickly evolved into the three sensors you see below:

![LegoSet](https://github.com/jackshiels/LightSense/blob/main/Images/Set.jpg?raw=true)

## Software

An MQTT server installed on my Raspberry Pi is used to collect data from the external and internal sensors. Then, the monitor subscribes to these data feeds and makes the monitor smile or frown, based on energy usage. The internal sensor code loop is shown below. It grabs the light value from an analog pin, which uses the resistance of the light input to determine analog voltage. This value is published to the MQTT server as a percentage value.

```
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
```

The monitor then reads these values and displays a smile or frown accordingly. The smile or frown are based on the light values gleaned from the external and internal sensors:

```
void mqttReader(char* topic, byte* payload, unsigned int length){
  convertedMessage = reinterpret_cast<const char*>(payload);
  messageNumeric = atoi(convertedMessage);
  if (strcmp(topic, "home/room/bedroom/light") == 0){
    internalLight = messageNumeric;
  }
  if (strcmp(topic, "home/room/bedroom/movement") == 0){
    movement = messageNumeric;
  }
  if (strcmp(topic, "home/external/light") == 0){
    externalLight = messageNumeric;
  }
}
```

The final result can be seen in the video here: https://youtu.be/dj-cJYu9SqU

## Reflections

Below are a few reflections on the project and areas for improvement:

- Soldering is hard! I ruined some parts trying to solder an open PCB. It would be far better to print my own board and have it made for me.
- Social pressure from my monitor device feels effective and is perhaps better than an automatic solution.
- I would have liked to include additional energy sensors such as temperature from heat, but I ran out of time.
- Lego is an EXTREMELY effective rapid prototyping solution, but would not be good for real-world installations.

Jack Shiels

# References
<a id="1">[1]</a>
Mason, R. & Elliot, L. (2022). <i>Millions of UK households to pay more for energy from April</i>. Available at: [https://www.theguardian.com/politics/2022/nov/16/millions-of-uk-households-to-pay-more-for-energy-from-april](https://www.theguardian.com/politics/2022/nov/16/millions-of-uk-households-to-pay-more-for-energy-from-april) (Accessed: 27 November 2022).

<a id="2">[2]</a>
Amazon EU Sarl (2022). <i>AZDelivery 3 x ESP32-DevKitC NodeMCU WiFi WLAN CP2102 ESP32-WROOM-32D IoT 2-In-1 Microcontroller Bluetooth Module Development Board compatible with Arduino including E-Book!</i>. Available at: [https://amzn.eu/d/5WvY7B8](https://amzn.eu/d/5WvY7B8) (Accessed: 27 November 2022).

<a id="3">[3]</a>
Amazon EU Sarl (2022). <i>AZDelivery 5 x Compatible with HC-SR501 PIR Infrared Motion Detection Sensor Module compatible with Arduino and Raspberry Pi including E-Book!</i>. Available at: [https://www.amazon.co.uk/AZDelivery-HC-SR501-Detection-Raspberry-including/dp/B07V9GFHFW](https://www.amazon.co.uk/AZDelivery-HC-SR501-Detection-Raspberry-including/dp/B07V9GFHFW) (Accessed: 27 November 2022).

<a id="4">[4]</a>
Amazon EU Sarl (2022). <i>AZDelivery Digital Temperature And Humidity Sensor Module 3.3V 5V Compatible with DHT22 Compatible with AM2302 Replace SHT11 SHT15 Compatible With Arduino and Raspberry Pi Including E-Book!</i>. Available at: [https://amzn.eu/d/iVrD5Em](https://amzn.eu/d/iVrD5Em) (Accessed: 27 November 2022).

<a id="5">[5]</a>
Amazon EU Sarl (2022). <i>Raspberry Pi 4 Model B (4GB)</i>. Available at: [https://www.amazon.co.uk/Raspberry-Pi-Model-4GB/dp/B09TTNF8BT](https://www.amazon.co.uk/Raspberry-Pi-Model-4GB/dp/B09TTNF8BT) (Accessed: 27 November 2022).

# Additional Inspirational Sources:
https://create.arduino.cc/projecthub/biharilifehacker/arduino-with-pir-motion-sensor-fd540a
https://learn.adafruit.com/dht
[https://www.youtube.com/watch?v=pxR6e-3XkIk](https://www.vishay.com/docs/81579/temt6000.pdf)
https://esphome.io/cookbook/temt6000.html
https://docs.arduino.cc/learn/microcontrollers/analog-input
https://pubsubclient.knolleary.net/api
https://workshops.cetools.org/codelabs/CASA0019-unity-mqtt/index.html?index=..%2F..index#0
https://cdn.shopify.com/s/files/1/1509/1638/files/ESP-32_NodeMCU_Developmentboard_Schematic_korr.pdf?v=1666000508
https://randomnerdtutorials.com/installing-the-esp32-board-in-arduino-ide-windows-instructions/
https://www.mischianti.org/images-to-byte-array-online-converter-cpp-arduino/

# Code credits

SSD1306 Code:
Modified from: https://github.com/adafruit/Adafruit_SSD1306

General MQTT Code:
Modified from: https://workshops.cetools.org/
