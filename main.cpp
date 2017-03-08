/*
   RoboUke - Trainable Robotic Ukulele System
   Nick Howarth & Sam Wolfson, Team Fox
   ESE 350 - Introduction to Embedded Systems and Microcontrollers, Spring 2012
*/

#include "playback.h"
#include "mbed.h"
#include "recordSensor.h"
#include "PlayBackFunctions.h"

#define LENGTH 16 // number of chords that can be stored on each channel
            // 16 is not necessarily the maximum number of chords that can be stored; just arbitrary

/* initialize LEDs on mbed */
DigitalOut myLED1(LED1);
DigitalOut myLED2(LED2);
DigitalOut myLED3(LED3);
DigitalOut myLED4(LED4);

/* initialize button inputs */
DigitalIn record_button1(p7); // button 1
DigitalIn record_button2(p8); // button 2
DigitalIn prerec_button(p11); // button 5
DigitalIn playback_button2(p13); // button 7
DigitalIn playback_button1(p14); // button 8

Serial pc(USBTX, USBRX); // tx, rx; initialize serial communication

int main() {
    /* allocate space for arrays to store chords/timing */
    unsigned short int* ctarray1 = (unsigned short int *) malloc (sizeof(unsigned short int) * LENGTH);
    unsigned short int* ctarray2 = (unsigned short int *) malloc (sizeof(unsigned short int) * LENGTH);
    /* chords/timing array for demo song ("Good King Wenceslas") */ 
    unsigned short int prerecSong[16] = {41200, 40600, 40600, 50600, 40600, 40600, 10600, 21200, 10600, 20600, 30600, 40600, 41200, 0, 0, 0};

    while (1) {
        while ((record_button1)) { // while recording on channel 1
            /* "Countdown" from LED4 to LED1 -- start playing on LED1 */
            myLED4 = 1; 
            wait(1);
            myLED4 = 0;
            myLED3 = 1;
            wait(1);
            myLED3 = 0;
            myLED2 = 1;
            wait(1);
            myLED2 = 0;
            myLED1 = 1;
            recordSensor(&ctarray1); // record chord/timing data into array for channel 1
        }
        myLED1 = 0; // turn off LED1 when record_button1 turned off

        while (record_button2) { // while recording on channel 2
            /* "Countdown" from LED4 to LED1 -- start playing on LED1 */
            myLED4 = 1;
            wait(1);
            myLED4 = 0;
            myLED3 = 1;
            wait(1);
            myLED3 = 0;
            myLED2 = 1;
            wait(1);
            myLED2 = 0;
            myLED1 = 1;
            recordSensor(&ctarray2); // record chord/timing data into array for channel 2
        }
        myLED1 = 0; // turn off LED1 when record_button2 turned off
        
        servoInit(); // initialize servos to prepare for playback
        while (playback_button1) { // while playing back recording on channel 1
            myLED2 = 1; // turn on LED2 to signify playback mode
            playback(ctarray1); // play song stored on channel 1
        }
        myLED2 = 0; // turn off LED2 when playback_button1 turned off

        servoInit(); // initialize servos to prepare for playback
        while (playback_button2) { // while playing back recording on channel 2
            myLED2 = 1; // turn on LED2 to signify playback mode
            playback(ctarray2); // play song stored on channel 2
        }
        myLED2 = 0; // turn off LED2 when playback_button2 turned off

        servoInit(); // initialize servos to prepare for playback
        while (prerec_button) { // while playing back demo track
            myLED3 = 1; // turn on LED3 to signify demo track playback
            playback(prerecSong); // play demo track
        }
        myLED3 = 0; // turn off LED3 when prerec_button turned off
    }
}

