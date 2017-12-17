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
        selection=-1;
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
        if(selection==-1) 
            return this;
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
    void setValue(int v)
    {
        index=v;
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
DigitAction scaleDigit(7);

static void updateScreenAndGen(void);
/**
 * 
 */
void initLoop()
{   
    top.addAction(&waveForm);
    top.addAction(&hiDigit);
    top.addAction(&loDigit);
    top.addAction(&scaleDigit); 
    hiDigit.setValue(1);
    loDigit.setValue(0);
    scaleDigit.setValue(3); // 1khz default value
    updateScreenAndGen();
}
/**
 * 
 */
static const char *unit[3]={"Hz","kHz","MHz"};

void updateScreenAndGen()
{
      char buffer[16];
        float finalFq;
//        return;
        // compute the fq
        int range=scaleDigit.getIndex();
        int mul=range%3,mul2=mul;
        
        int fq=hiDigit.getIndex()*10+loDigit.getIndex();
        finalFq=fq;
        for(int i=0;i<range;i++)
            finalFq*=10.;
        finalFq/=10.;

        gen->setWaveForm((WavWave)waveForm.getIndex());
        gen->setFrequency(finalFq);
        
        
        range=range/3;        
        

        
        if(mul)
        {
            while(--mul) fq=fq*10;
        }
        
        if(mul2)
        {
            sprintf(buffer,"%3d%s",fq,unit[range]);
        }else
            sprintf(buffer,"%1d.%1d%s",hiDigit.getIndex(),loDigit.getIndex(),unit[range]);
            
        
        
        display->startRefresh();        
        // 0 24
        display->draw(top.getIndex(),top.getSelection()+1,waveForm.getIndex(),hiDigit.getIndex(),loDigit.getIndex(),scaleDigit.getIndex(),buffer);
        display->endRefresh();
}

void runLoop()
{
    
    bool changed=true;
    Action *currentWidget=top.getCurrent();
    switch(rotary->getSense())
    {
        default:
            changed=false;
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
        changed=true;
    }
    if(changed)
    {
        updateScreenAndGen();
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


