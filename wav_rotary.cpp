
#include "Rotary.h"
#include "wav_rotary.h"
/**
 */
 WavRotary::WavRotary(int pinA,int pinB, int pinButton) : _rotary(pinA,pinB)
 {
    _pushButton=pinButton;   
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
 bool         WavRotary::getPushButtonStatus()
 {
     return false;
 }

 // EOF