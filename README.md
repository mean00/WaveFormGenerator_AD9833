# WaveFormGenerator_AD9833
Simple waveform generator, using AD9833 + rotary encoder + SSD1306 oled screen.
It can output triangle/sinusoidal/rectangular waveforms.

That project is using lnArduino and requires a GD32F1/GD32F3/GD32VF1 or STM32F1 (bluepill)

Build instruction :
* edit platformConfig to specify your toolchain location
* edit mcuSelect.cmake to select your chip (default it GD32F1/STM32F1)
* mkdir build
* cd build && cmake ..
* make


Careful on the opamp.
Take one that is :
* Rail to rail
* Have high enough V/us rising time
* Have high enough gain x bandwidth ratio

With a MCP602 as amplifider, the signal is good till ~ 350 kHz
With a LM358 it's much lower, like ~ 150 kHZ

The square signal is directly from the ad9833 to avoid it being smoothed by the opamp.

![screenshot](schematics/ad_front.jpg?raw=true "front")
![screenshot](schematics/ad_top.jpg?raw=true "top")
![screenshot](schematics/schematic.pdf?raw=true "schem")

