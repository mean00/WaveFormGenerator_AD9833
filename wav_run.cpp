/**
 */
#include <AD9833.h>
#include <Rotary.h>
#include "wav_display.h"
#include "wav_rotary.h"
#include "wav_gen.h"

extern WavDisplay      *display;
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
    virtual void setParent(Action *a) {}
};
/**
 */
class TopAction : public Action
{
public:
    TopAction()
    {
        index=0;
        max=0;
        selection-1;
    }
    virtual void turnLeft()
    {
        index=(index+max-1)%max;
    }
    virtual void turnRight()
    {
        index=(index+1)%max;
    }
    virtual void shortPress()
    {
        selection=index;
    };
    int getIndex() 
    {
        return index;
    }
    void addAction(Action *a)
    {
        actions[max]=a;
        a->setParent(this);
        max++;
    }
    Action *getCurrent()
    {
        if(selection==-1) return this;
        return actions[selection];
    }
    int  getSelection()
    {
        return selection;
    }
    void exitSelection()
    {
        selection=-1;
    }

protected:
    int     index;
    int     max;
    Action  *actions[10];
    int     selection;
};
/**
 * 
 */
class DigitAction : public Action
{
public:
    DigitAction(int mx)
    {
        index=0;
        _parent=NULL;
        _max=mx;
    }
    virtual void turnLeft()
    {
        index=(index+_max-1)%_max;
    }
    virtual void turnRight()
    {
        index=(index+1)%_max;
    }
    virtual void shortPress()
    {
        ((TopAction *)_parent)->exitSelection(); // Ugly but simple
    };
    int getIndex() {return index;}
    virtual void setParent(Action *a) {_parent=a;}
protected:
    int     index;
    Action *_parent;
    int     _max;
    
};


TopAction   top;
DigitAction waveForm(3);
DigitAction hiDigit(10);
DigitAction loDigit(10);
DigitAction scaleDigit(5);


/**
 * 
 */
void initLoop()
{   
    top.addAction(&waveForm);
    top.addAction(&hiDigit);
    top.addAction(&loDigit);
    top.addAction(&scaleDigit); 
}
/**
 * 
 */
void runLoop()
{
    static int dbg=0;
    bool redraw=true;
    Action *currentWidget=top.getCurrent();
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
    if(rotary->getPushButtonStatus())
    {
        currentWidget->shortPress();
        redraw=true;
    }
    if(redraw)
    {
        display->startRefresh();        
        // 0 24
        display->draw(top.getIndex(),top.getSelection()+1,waveForm.getIndex(),hiDigit.getIndex(),loDigit.getIndex(),scaleDigit.getIndex());
        display->endRefresh();
    }
    delay(100); // wait 100ms
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


