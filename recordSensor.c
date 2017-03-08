/*
   RoboUke - Trainable Robotic Ukulele System
   Nick Howarth & Sam Wolfson, Team Fox
   ESE 350 - Introduction to Embedded Systems and Microcontrollers, Spring 2012
*/

#include "mbed.h"

#define ON_THRESHOLD 0.90 // threshold value to register strum on microphone
#define LENGTH 16 // number of chords that can be stored on each channel

BusIn notes(p21, p22, p23, p24, p25, p26);  // initialize bus corresponding to signals from pressure sensors on fretboard
         //  E1,  C1,  A2,  C2,  E4,  A3  --  String/Fret

Timer t; // initialize timer object
AnalogIn mic(p20); // initialize analog input for microphone on p20
DigitalIn recordbutton1(p7); // recreate instance of record_button1
DigitalIn recordbutton2(p8); // recreate instance of record_button2
/* initialize analog input pins adjacent to p20 (mic) */
DigitalOut dout1(p19);
DigitalOut dout2(p18);
DigitalOut dout3(p17);
DigitalOut dout4(p16);
DigitalOut dout5(p15);

void recordSensor(unsigned short int** ctarray) {
    short int end = 0;
    short int last = 0;
    short int i = 0;
    short int begin = 1; 
    float micval;
    unsigned short int timedif;
    unsigned short int chordID;
    /* set all digital output pins next to mic to 0 (to ensure no interference to ADC on p20) */
    dout1 = 0;
    dout2 = 0;
    dout3 = 0;
    dout4 = 0;
    dout5 = 0;

    t.reset(); // reset timer to 0
    while ((recordbutton1 || recordbutton2) && (!end)) {  // while recording / not finished recording
        if (begin) {  // only run this at beginning of record mode
            t.start(); // start timer
            begin = 0; // ensure this part is not run again
            for (int j = 0; j < LENGTH; j++) {
                *((*ctarray) + j) = 0;  // clear all elements of ctarray
            }
        }
        micval = mic.read(); // perform ADC on p20, store float value into micval
        if (micval >= ON_THRESHOLD) { // if strum detected
            t.stop(); // stop timer
            timedif = t.read_ms(); // store time (in ms) between strums
            switch (notes) {  // identify chord based on state of pressure sensors
                case 32: // 0b000001 -> 0b100000
                    chordID = 1; // C chord
                    break; 
                case 8: // 0b000100 -> 0b001000
                    chordID = 2; // D chord
                    break; 
                case 20: // 0b001010 -> 0b010100
                    chordID = 3; // E chord
                    break; 
                case 16: // 0b000010 -> 0b010000
                    chordID = 3; // E chord
                    break; 
                case 1: // 0b100000 -> 0b000001
                    chordID = 4; // F chord
                    break; 
                case 12: // 0b001100 -> 0b001100
                    chordID = 5; // G chord
                    break; 
                case 2: // 0b010000 -> 0b000010
                    chordID = 6; // A chord
                    break; 
                default :
                    chordID = 0; // no chord detected
                    last = 1; // signify end of recording
                    break;
            }
            *((*ctarray) + i) = chordID * 10000 + timedif; // concatenate chordID and time difference into integer, store in ctarray
            i++;  // move to next space in array
            if (last)  // if strum registered with no chord, stop recording
                end = 1;
            t.reset(); 
            t.start(); 
            wait(.5); // wait .5s before checking for another strum (to ensure multiple strums are not registered for each strum)
        }
    }
}