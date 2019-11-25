# WeatherCloud
This code controls a artifical cloud that is activated by movement and then displays the current weather using different LEDs and  lighting patterns.

As soon as the optical motion sensor sense movement below the cloud the current weather will be displayed with LEDs. Pulsating yellow light represents good weather, blue/white light represents cloudy weather, white pulsating light snowy weather (because I do love snow) and rain/thunderstorms using bright white LEDs flashing. 

During late night hours only blue pulsating light will be displayed to use the cloud as a relaxing night light. 

The time is requested from a NTP server (ntpudp) and weather using yahoo's weather API. 

To use the code you have to enter your routers SSID and password and change the yahoo API adress. You also might have to adapt it to your time zone. 

I used an ESP8266 as controller and the LEDs were switched on/off using MOSFETS (RFP30N06LE). More on that matter can be found for example here: https://bildr.org/2012/03/rfp30n06le-arduino/

![alt text](https://github.com/dermanu/WeatherCloud/blob/master/Lightning.mp4)


