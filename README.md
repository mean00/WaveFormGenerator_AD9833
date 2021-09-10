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

![screenshot](schematics/pic.jpg?raw=true "front")
![screenshot](schematics/schematic.png?raw=true "schem")

