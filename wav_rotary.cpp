
#include "Rotary.h"
#include "wav_rotary.h"
/**
 */
 WavRotary::WavRotary(int pinA,int pinB, int pinButton) : _rotary(pinA,pinB)
 {
     
    _pushButton=pinButton;   
    pinMode(_pushButton, INPUT_PULLUP);     
    _count=0;
 }
 /**
  */
 WavDirection WavRotary::getSense()
 {
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
     bool s=  digitalRead(_pushButton); // very simple debounce
     if(!s)
         _count++;
     else
         _count=0;
     if(_count>4) return true;
     return false;
 }

 // EOF