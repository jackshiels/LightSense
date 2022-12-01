

# LightSense
<b>Jack Shiels</b>
A project for UCL's CASA0016 module for building connected environments

# Problem - Energy Costs £££'s!
The advent of the Russia-Ukraine war created an unstable energy market, leading to some serious costs for the average Briton [[1]](#1). As such, many will seek to minimise their energy costs as Winter approaches. The Internet of Things (IoT) could help to mend this situation through careful energy management and social conditioning to prevent wastage. The aim of this project is to remind individuals to monitor their energy usage when it comes to indoor lighting.

# Solution: LightSense Light Monitoring and Presentation
Energy can take many forms - heat, light, sound, and many more. However, what's the use of energy if it is not being enjoyed by the user? 

LightSense is a family of small sensor units with a specific purpose - to track light and temperature levels in rooms, correlate them with human occupation of those rooms, and recommend the user adjusts their energy usage when room energy is being wasted. For example, a room may be left with the lights on, but nobody is there. This is a waste! Similarly, a window may be left open, leading to an unacceptable drop in temperature when the user arrives home. In this case, valuable heat energy is lost. Preventative alerts allow both situations to be avoided or mitigated. 

This project was designed when creating some quick sketches for an IoT architecture. Originally, the data would be displayed on a web page, but this was extended to include a 3D rendering of the home.

![Architecture diagram](https://github.com/jackshiels/LightSense/blob/main/Images/Sketchup.jpg?raw=true)

## Proposed Architecture
A diagram of the detailed architecture is rendered below:

![Architecture diagram](https://github.com/jackshiels/LightSense/blob/main/Images/LightSenseArchitecture.png?raw=true)

LightSense sensors are split into two types of units: interior and exterior. The exterior sensor grabs the external temperature and ambient light level to get a "baseline" reading. This data is then sent to InfluxDB on the Raspberry Pi. An internal sensor captures local data, meaning a comparison can be made between the internal and external light and temperature values. Additionally, the internal sensor captures motion with a PIR sensor tuned to provide updates at a minute interval. Lastly, these values are displayed in a Unity3D application that renders a 3D model of the home, complete with alerts that show when specific rooms are occupied.

Parts that I intend to use include:

ESP32 boards [[2]](#2):

![ESP32 boards](https://m.media-amazon.com/images/I/A1Ttq+6868L._SX522_.jpg)

PIR sensors [[3]](#3):

![PIR sensors](https://m.media-amazon.com/images/I/71RI9JGggML._SX522_.jpg)

DHT22 temperature sensors [[4]](#4):

![Temperature sensor](https://m.media-amazon.com/images/I/61CC4PSVW2L._SX522_.jpg)

Raspberry Pi 4GB [[5]](#5):

![Raspberry Pi](https://m.media-amazon.com/images/I/912ja-jKOfL._AC_SX425_.jpg)

By understanding when rooms are left empty with lights on, or heat is being lost, the user can better manage their energy usages throughout the home. A further application of the project is home security monitoring using the PIR sensors. The Unity3D executable may even be turned into an iOS or Android application. Some potential downsides include:

* The need for sensor "tuning" against the baseline e.g., is the external light sensor able to capture ambient light effectively? What if the reflection of a car window shines on the light sensor?
* It is not yet certain if an otherwise unheated home will naturally tend to the outside temperature (maybe the insulation is a "free" heating boost to the property).

Despite these challenges, the project will be an interesting foray into the world of energy sensing, and provides a foundation from which to design even more technically advanced projects in future.

## Some questions for discussion:

* What arduino boards would you recommend? Are ESP32 boards a good choice?
* How will these be powered?
* How could the light sensor be replaced with an embedded light switch monitor?

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

# Additional Sources:
https://create.arduino.cc/projecthub/biharilifehacker/arduino-with-pir-motion-sensor-fd540a
