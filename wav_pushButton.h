

#pragma once

class WavPushButton
{
public:
           WavPushButton(int pin,int interval);
      void run();
      bool pressed();

protected:
    Bounce          _bounce;
    int             _pin;
    bool            _changed;
};