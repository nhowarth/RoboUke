/*
   RoboUke - Trainable Robotic Ukulele System
   Nick Howarth & Sam Wolfson, Team Fox
   ESE 350 - Introduction to Embedded Systems and Microcontrollers, Spring 2012
*/

#include "PlayBackFunctions.h"
#include "mbed.h"

#define LENGTH 16 // number of chords that can be stored on each channel

void playback(unsigned short int* ctarray) {
    /* recreate instances of playback buttons for use within function */
    DigitalIn playback1(p14);
    DigitalIn playback2(p13);
    DigitalIn pre_rec(p11);

    for (int l = 0; l < LENGTH; l++) {  // cycle through elements in array
        if (!(playback1 || playback2 || pre_rec)) {  // if none of the buttons are pressed, break out of function
            break;
        }
        if (ctarray[l] != 0) {  // if array element is not 0 (i.e., something has been recorded at element l)
            wait_ms((ctarray[l] % 10000) - 100);  // wait between chords, give margin of time to change chord before strumming
            if ((ctarray[l] / 10000) == 0)  // if chord not registered, break
                break;
            changeChord(ctarray[l] / 10000);  // change chord
            wait(.1); 
            strummer();  // activate strum
        }
    }
}