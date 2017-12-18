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
// Need to include these here, so that cmake finds them
#include <SPI.h>
#include <Wire.h>
#include <AD9833.h>
#include <Rotary.h>
#include <U8g2lib.h>
//

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
    display=new WavDisplay(8,9,10); // +11 & 13 for hw SPI
    rotary= new WavRotary(3,2,4);
    gen=    new WavGenerator(5);;   // +11 /13 for hw spi
//    gen->setWaveForm(WavTriangle);
//    gen->setFrequency(1000);
    display->displayStatus("Go");
    initLoop();
    Serial.println("*Setup done*");
}
/**
 * 
 */
void loop() 
{ 
    runLoop();       
}

// EOF


