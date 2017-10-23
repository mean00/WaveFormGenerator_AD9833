/*
 * AD9833_test_suite.ino
 * 2016 WLWilliams
 * 
 * This sketch demonstrates the use of the AD9833 DDS module library.
 * 
 * If you don't have an oscilloscope or spectrum analyzer, I don't quite know how you will
 * verify correct operation for some of the functions.
 * TODO: Add tests where the Arduino itself vereifies AD9833 basic operation.  Frequency of
 * square wave, sine/triangular wave using the A/D inputs (would need a level shifter).
 * 
 * This program is free software: you can redistribute it and/or modify it under 
 * the terms of the GNU General Public License as published by the Free Software Foundation,
 * either version 3 of the License, or (at your option) any later version. 
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details. You should have received a copy of
 * the GNU General Public License along with this program.
 * If not, see <http://www.gnu.org/licenses/>. 
 *
 * This example code is in the public domain.
 * 
 * Library code found at: https://github.com/Billwilliams1952/AD9833-Library-Arduino
 * 
 * Rotarty encoder
 * https://www.allaboutcircuits.com/projects/how-to-use-a-rotary-encoder-in-a-mcu-based-project/
 * https://github.com/brianlow/Rotary
 */

#include <SPI.h>
#include <AD9833.h>
#include <Rotary.h>
#include "wav_display.h"
#include "wav_rotary.h"
#include "wav_gen.h"
#include "wav_run.h"


extern void runLoop(void);

WavDisplay      *display;
WavRotary       *rotary;
WavGenerator    *gen;


/**
 * 
 */
void setup() 
{ 
    while (!Serial);          // Delay until terminal opens
    Serial.begin(57600);
    Serial.println("*Start*");
    display=new WavDisplay;
    rotary= new WavRotary(1,2,3);
    gen=    new WavGenerator(4);
    Serial.println("*Init done*");
    display->displayStatus("Go");
}
/**
 * 
 */
void loop() 
{ 
    runLoop();
   
    
}


