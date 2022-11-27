

# LightSense
<b>Jack Shiels</b>
A project for UCL's CASA0016 module for building connected environments

# Problem - Energy Costs £££'s!
The advent of the Russia-Ukraine war created an unstable energy market, leading to some serious costs for the average Briton [[1]](#1). As such, many will seek to minimise their energy costs as Winter approaches. The Internet of Things (IoT) could help to mend this situation through careful energy management and social conditioning to prevent wastage. The aim of this project is to remind individuals to monitor their energy usage when it comes to indoor lighting.

# Solution: LightSense Light Monitoring and Presentation
Energy can take many forms - heat, light, sound, and many more. However, what's the use of energy if it is not being enjoyed by the user? 

LightSense is a family of small sensor units with a specific purpose - to track light and temperature levels in rooms, correlate them with human occupation of those rooms, and recommend the user adjusts their energy usage when room energy is being wasted. For example, a room may be left with the lights on, but nobody is there. This is a waste! Similarly, a window may be left open, leading to an unacceptable drop in temperature when the user arrives home. In this case, valuable heat energy is lost. Preventative alerts allow both of these situations to be avoided or mitigated. 

This project was designed when creating some quick sketches for an IoT architecture. Originally, the data would be displayed on a web page, but this was extended to include a 3D rendering of the home.

![Architecture diagram](https://github.com/jackshiels/LightSense/blob/main/Images/Sketchup.jpg?raw=true)

A diagram of the detailed architecture is rendered below:

![Architecture diagram](https://github.com/jackshiels/LightSense/blob/main/Images/LightSenseArchitecture.png?raw=true)

LightSense sensors are split into two types of units: interior and exterior. The exterior sensor grabs the external temperature and ambient light level to get a "baseline" reading. This data is then sent to InfluxDB on the Raspberry Pi. An internal sensor captures local data, meaning a comparison can be made between the internal and external light and temperature values. Additionally, the internal sensor captures motion with a PIR sensor tuned to provide updates at a minute interval. Lastly, these values are displayed in a Unity3D application that renders a 3D model of the home, complete with alerts that show when specific rooms are occupied.

By understanding when rooms are left empty with lights on, or heat is being lost, the user can better manage their energy usages throughout the home. A further application of the project is home security monitoring using the PIR sensors. The Unity3D executable may even be turned into an iOS or Android application. Some potential downsides include:

* The need for sensor "tuning" against the baseline e.g., is the enternal light sensor able to capture ambient light effectively? What if the reflection of a car window shines on the light sensor?
* It is yet unknown if 
* It is not yet certain if an otherwise unheated home will naturally tend to the outside temperature (maybe the insulation is a "free" heating boost to the property).

Despite these challenges, the project will be an interesting foray into the world of energy sensing, and provides a foundation from which to design even more technically advanced projects in future.

Jack Shiels

# References
<a id="1">[1]</a>
Mason, R. & Elliot, L. (2022). <i>Millions of UK households to pay more for energy from April</i>. Available at: [https://www.theguardian.com/politics/2022/nov/16/millions-of-uk-households-to-pay-more-for-energy-from-april](https://www.theguardian.com/politics/2022/nov/16/millions-of-uk-households-to-pay-more-for-energy-from-april) (Accessed: 27 November 2022).
