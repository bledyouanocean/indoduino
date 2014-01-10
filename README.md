indoduino
=========

arduino indoor garden



   I have recently released my third beta version of the indoduino prototype. java app writen in processing. not the most elaborate of all apps, but its all i know how to do so far. this most recent update is in use on a Raspberry pi all libraries required for compiling are included, and a precompiled package is available for all platforms. will also include an updated image of my raspberry pi so if you want to be able to run processing and develop immediately you can just write the OS image to an sdcard, and go from there. the server app will be available right on the desktop.

   I have also included a fritzing project for an arduino sheild that would house all the hardware directly on top of the arduino. the sheild is designed for an arduino mega2560. 

   Please forgive me, but I must get in the habit of commenting more often in my code. will be spending the next couple of days going through and commenting on what needs to be changed, and also providing an option in the client sketch to allow user to specify IP address/port of camera, and data server.




on arduino {
DHT11
6 relay channels(light, timed pump, soil pump *2, heater, air-conditioner/fan)
DS1307 RTC
2 analog soil moisture sensors
}


on raspberry pi {
processing
ps eye webcam
arduino
}

 ^see what i did there?
 
 
 























