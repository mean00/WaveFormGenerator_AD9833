

#pragma once

#include "string"
/**
 */
enum WaveForm
{
    WAVE_SINE=0,
    WAVE_TRIANGLE=1,
    WAVE_SQUARE=2,
};

enum Selection
{
    TOP_SELECTION,
    WAVEFORM_SELECTION,
    HIDIGIT_SELECTION,
    LODIGIT_SELECTION,
    SCALE_SELECTION,
};
/**
 * 
 */
class ActionInterface
{
public:
            ActionInterface() {}
    virtual ~ActionInterface() {};
    virtual int getFrequency()=0;
    virtual void getFrequencyAsString(char *out, int maxSize)=0;
    virtual int getNumber(int rank)=0;
    virtual bool run(lnRotary::EVENTS  event,int ticks)=0;
    virtual WaveForm getWaveForm()=0;
    virtual Selection selection()=0;
    virtual int selectionIndex()=0;
};

ActionInterface *createActionInterface();
//EOF