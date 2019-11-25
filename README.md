# WeatherCloud
This code controls a artifical cloud that is activated by movement and then displays the current weather using different LEDs and  lighting patterns.

As soon as the optical motion sensor sense movement below the cloud the current weather will be displayed with LEDs. Pulsating yellow light represents good weather, blue/white light represents cloudy weather, white pulsating light snowy weather (because I do love snow) and rain/thunderstorms using bright white LEDs flashing. 

During late night hours only blue pulsating light will be displayed to use the cloud as a relaxing night light. 

The time is requested from a NTP server (ntpudp) and weather using yahoo's weather API. 

To use the code you have to enter your routers SSID and password and change the yahoo API adress. You also might have to adapt it to your time zone. 

I'll soon upload pictures of the cloud and might create a electrical circuit file.
