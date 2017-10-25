
#pragma once
#include "Bounce2.h"
/**
 */
enum WavDirection
{
  WavNone=0,
  WavLeft,
  WavRight
};
/**
 */
class WavRotary
{
public:
                     WavRotary(int pinA,int pinB, int pinButton);
        WavDirection getSense();
        bool         getPushButtonStatus();    
protected:
        Rotary       _rotary;
        int          _pushButton;
        Bounce       _bounce;
};