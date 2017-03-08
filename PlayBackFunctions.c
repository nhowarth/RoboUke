/*
   RoboUke - Trainable Robotic Ukulele System
   Nick Howarth & Sam Wolfson, Team Fox
   ESE 350 - Introduction to Embedded Systems and Microcontrollers, Spring 2012
*/

#include "mbed.h"

/* chord servos are on CT16B0/MR0 */
PwmOut ServoCD(p5); 
PwmOut ServoEF(p6);
PwmOut ServoGA(p34);
/* strum servo is on CT16B1/MR1 */
PwmOut strum(p36); 

unsigned short int dir; // strum direction

void servoInit() {  
 /* initialize PWM clocks */
    LPC_CT16B0->TCR = 2;
    LPC_CT16B0->PR = 19;
    LPC_CT16B0->MR3 = 48000;
    LPC_CT16B0->TCR = 1;

    LPC_CT16B1->TCR = 2;
    LPC_CT16B1->PR = 19;
    LPC_CT16B1->MR3 = 48000;
    LPC_CT16B1->TCR = 1;
    
 /* initialize servos to neutral positions */
    ServoCD = 0.075; 
    ServoEF = 0.045; 
    ServoGA = 0.060; 
    strum = 0.07; 

    dir = 0; // initialize strum direction
}

void strummer() {
    if (!dir) {
        strum = 0.10; // strum down (G string -> A string)
        dir = 1;
    } else if (dir) {
        strum = 0.07; // strum up (A string -> G string)
        dir = 0;
    }
}

void changeChord(int c) {
    if (c == 1) {
        ServoCD = 0.075; // C chord pwm duty cycle value on p5
        ServoEF = 0.045; // neutral position
        ServoGA = 0.060; // neutral position
    } else if (c == 2) {
        ServoCD = 0.046; // D chord pwm duty cycle value on p5
        ServoEF = 0.045; // neutral position
        ServoGA = 0.060; // neutral position
    } else if (c == 3) {
        ServoEF = 0.073; // E chord pwm duty cycle value on p6
        ServoCD = 0.075; // servocd in neutral position
        ServoGA = 0.060; // neutral position
    } else if (c == 4) {
        ServoEF = 0.017; // F chord pwm duty cycle value on p6
        ServoCD = 0.075; // neutral position
        ServoGA = 0.060; // neutral position
    } else if (c == 5) {
        ServoGA = 0.082; // G chord pwm duty cycle value on p34
        ServoEF = 0.045; // neutral position
        ServoCD = 0.075; // neutral position
    } else if (c == 6) {
        ServoGA = 0.040; // A chord pwm duty cycle value on p34
        ServoEF = 0.045; // neutral position
        ServoCD = 0.075; // neutral position
    }
}