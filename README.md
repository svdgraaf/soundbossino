Soundbossino
============
A [Soundboss](https://github.com/dkln/soundboss) Arduino Websocket client

Yes, it's an awesome overkill application for something very simple, but did I mention it is just awesome?

Parts list
==========
- [Arduino (R3)](http://www.pieterfloris.nl/shop/product.php?id_product=485)
- [Arduino network shield](http://www.pieterfloris.nl/shop/product.php?id_product=101) or [Wifi shield](http://www.pieterfloris.nl/shop/product.php?id_product=808)
- [Big Red Button](http://www.pieterfloris.nl/shop/product.php?id_product=162) or [similair](http://www.pieterfloris.nl/shop/product.php?id_product=167), or any other bit button, just make sure it's a 3 terminal switch
- 10k ohm resistor (optional, some buttons need it)

Wiring
======
![wiring](https://raw.github.com/svdgraaf/soundbossino/master/sketch.png)

Building
========
Make sure you have the latest [Arduino package](http://arduino.cc/en/Main/Software).

The soundbossino uses the awesome [Arduino Websocket client](https://github.com/krohling/ArduinoWebsocketClient) library, make sure to put that library in your Arduino Libraries folder (eg: Documents/Arduino)

Solder your resistor (if you have one), onto your wiring (see diagram above), and connect the wires to right ports. Load up the soundboss.ino file in your Arduino app, and connect your Arduino via the USB cable. Upload your software to your arduino. After upload, connect your network cable, reset your Arduino, and you should see the arduino connect to the Soundboss server in the logs. After that, just press the button, and you're all set!

Video
=====
[![Youtube video here](http://img.youtube.com/vi/VEaQiwvT0Hs/0.jpg)](http://www.youtube.com/watch?v=VEaQiwvT0Hs)