# RoboUke
Trainable Robotic Ukulele Player 

Authors: Nick Howarth and Sam Wolfson 
University of Pennsylvania, Dept. of Electrical and Systems Engineering, 
Embedded Systems (ESE 350), Spring 2012 

Video:  https://www.youtube.com/watch?v=GBdJjw4CUJE 

Blog:   http://robouke.blogspot.com/ 

Platform: mbed NXP LPC11U24 

Compile Instructions:  Import code into the mbed.org online compiler, press compile and download to mbed NXP LPC11U24. 

Structure: 

PlayBackFunctions.c contains the chordChange, strummer, and servoInit functions. 

playback.c contains the playback function, which uses the functions described in PlayBackFunctions.c to take an array of ints, 
parse them, and actuate the tune on the slave ukulele. 

recordSensor.c contains the function to detect strum duration and identify chords. 

main.cpp uses the functions described in playback.c and recordSensor.c for the top-level operation of the system. 
This is where direct interaction with the environment occurs, via the sensors and switches wired to the mbed. 
