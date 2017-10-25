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
#include "wav_gen.h"
 WavGenerator::WavGenerator(int csPin) : _gen(csPin)
 {
     _cs=csPin;
     _gen.Begin();
     _gen.EnableOutput(true);
 }
/**
 */
 void    WavGenerator::setWaveForm(WavWave wave)
 {
     WaveformType waveType;
     switch(wave)
     {
     case WavSinus:
         waveType = SINE_WAVE;
         break;
     case WavTriangle:
         waveType = TRIANGLE_WAVE;
         break;
     case WavSquare:
         waveType = SQUARE_WAVE;
         break;
    }
    _gen.SetWaveform(REG1,waveType);   // Next waveform
    _gen.SetWaveform(REG0,waveType);
    _gen.SetOutputSource(REG1);        // 
 }
 /**
  */
void    WavGenerator::setFrequency(float fq)
{
    _gen.SetFrequency(REG1,fq);
}
// EOF