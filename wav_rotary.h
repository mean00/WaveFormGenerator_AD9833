
#pragma once
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
        int          _count;
};