#include <SPI.h> // just to pull pinMode
#include "Bounce2.h"
#include "wav_pushButton.h"

 WavPushButton::WavPushButton(int pin, int val)
 {
     _pin=pin;
     pinMode(_pin,INPUT_PULLUP);
     _bounce.attach(_pin);
     _bounce.interval(val);
     _changed=false;
 }
 void WavPushButton::run()
 {
     _changed=_bounce.update();
 }
bool WavPushButton::pressed()
 {
    if(!_changed) return false;
    return !_bounce.read(); // fell();)
 }
