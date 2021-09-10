

#pragma once

extern void initLoop();
extern bool runLoop(  lnRotary::EVENTS  event,int count);
extern int  getFrequency();

enum WaveForm
{
    WAVE_SINE=0,
    WAVE_TRIANGLE=1,
    WAVE_SQUARE=2,
};

extern WaveForm  getWaveForm();
//EOF