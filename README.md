# WaveFormGenerator_AD9833
Simple waveform generator, using AD9833 + rotary encoder + SSD1306 oled screen.
It can output triangle/sinusoidal/rectangular waveforms.

That project is using arduino-cmake-stm32 (that works for both AVR and STM32 build)
All the dependencies are pulled as git submodules, so you just need Arduino IDE and cmake installed.
That's it.

build instruction  & flash using usbasp:
* mkdir build
* cd build && cmake ..
* make
* bash ../flash.sh

![screenshot](schematics/pic.jpg?raw=true "front")


