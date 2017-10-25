
#include "Rotary.h"
#include "wav_rotary.h"



/**
 */
 WavRotary::WavRotary(int pinA,int pinB, int pinButton) : _rotary(pinA,pinB)
 {
     
    _pushButton=pinButton;   
    pinMode(_pushButton, INPUT_PULLUP);     
    _bounce.attach(_pushButton);
    _bounce.interval(150);
 }
 /**
  */
 WavDirection WavRotary::getSense()
 {
     _bounce.update();
     switch(_rotary.process())
     {
        case DIR_CW:   return WavLeft;break;
        case DIR_CCW:  return WavRight;break;
        default:
                        return WavNone;break;
     }
 }
 /**
  */
 bool         WavRotary::getPushButtonStatus()
 {
     return !_bounce.read();
 }

 // EOF