# Doorman - Apartment Door Edition

This code runs on an Arduino-compatible ESP8266-based board. Using a stepper motor and some 3D printed parts, it is intended to lock and unlock my apartment door for me.

It is much more finnicky than the one controlling the main apartment building door, as that one requires no moving parts. As such, it is currently not working IRL.

## Update

Slow progress has been made.

I am using a Qi wireless charger and a battery-backed USB power supply to maintain power when the door is open and the wireless charger disconnected.

I'm using clone of the [adafruit PowerBoost 1000](https://www.adafruit.com/product/2465) I had made in China as the heart of the battery-backed USB power supply. This was much cheaper, per unit, but some of the units have bad thermal issues and are nearly useless. Overall, it was probably about the same cost per functioning unit and I got to order my first custom-made PCBs.

I had trouble with the 5v stepper motor not making enough torque. I have experimented with a 12v stepper motor, but this does require adding a means of delivering 12v. I am currently using a modified laptop battery. I don't have a convenient way of keeping it charged like I do with the 5v system, but the capacity is large enough that I haven't needed to yet.

The biggest obstacle I have run into is a user experience one. When connected, the stepper motor must be used to unlock the door. Using the key to manually unlock the door can damage the device. What if my phone dies, but I have my keys on me? I would have to gingerly unlock the door manually, then likely fix the alignment of the stepper motor. I have two possible solutions: use a keypad or an rfid reader as a backup unlock method. I could keep the fob on my keychain. I could also install a position sensor of some sort on the stepper motor, so the microcontroller always knows what position it is in in addition to where is is supposed to be.
