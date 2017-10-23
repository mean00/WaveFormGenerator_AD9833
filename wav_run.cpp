/**
 */
#include <AD9833.h>
#include <Rotary.h>
#include "amp_display.h"
#include "wav_rotary.h"
#include "wav_gen.h"

extern ampDisplay      *display;
extern WavRotary       *rotary;
extern WavGenerator    *gen;


enum GuiState
{
    guiTop,
    guiForm,
    guiTopDigit,
    guiBottomDigit
};

GuiState state=guiTop;

#define MAX 3
/**
 */
class Action
{
public:
    virtual void turnLeft()=0;
    virtual void turnRight()=0;
    virtual void shortPress()=0;
};
/**
 */
class TopAction : public Action
{
public:
    TopAction()
    {
        index=0;
    }
    virtual void turnLeft()
    {
        index=(index+MAX-1)%MAX;
    }
    virtual void turnRight()
    {
        index=(index+1)%MAX;
    }
    virtual void shortPress()
    {
        
    };
    int getIndex() {return index;}
protected:
    int     index;
};

TopAction top;
Action *currentWidget=&top;

void runLoop()
{
    bool redraw=true;
    switch(rotary->getSense())
    {
        default:
            redraw=false;
            break;

        case WavLeft:
            currentWidget->turnLeft();
            break;
        case WavRight:
            currentWidget->turnRight();
            break;
    }
    if(redraw)
    {
        char ST[]="  ";
        ST[0]='A'+top.getIndex();
        display->displayStatus(ST);
    }
    
}


#if 0
    static int signal=0;
    switch(rotary->getSense())
    {
        default:
            break;

        case WavLeft:
            Serial.println("Clockwise\n");
            signal=(signal+2)%3;
            gen->SetWaveForm((WavWave)signal);
            display->displayStatus(">>");
            break;
        case WavRight:
            Serial.println("CounterClockwise\n");
            signal=(signal+1)%3;
            gen->SetWaveForm((WavWave)signal);
            display->displayStatus("<<");
            break;
    }
#endif    


