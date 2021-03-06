/**
 */
#include <AD9833.h>
#include <Rotary.h>
#include "Bounce2.h"
#include "wav_display.h"
#include "wav_irotary.h"
#include "wav_gen.h"
#include "wav_pushButton.h"
extern WavDisplay      *display;
extern WavRotary       *rotary;
extern WavGenerator    *gen;
extern WavPushButton   *pushButton;
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
    // Set amp control as output
    pinMode(6,OUTPUT);
    digitalWrite(6, LOW);
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
/**
 */
void updateScreenAndGen()
{
    char buffer[16];
    float finalFq;
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
/**
 * https://sites.google.com/site/qeewiki/books/avr-guide/external-interrupts-on-the-atmega328
 */
void runLoop()
{    
    bool changed=false;
    
    
    int sense=rotary->getCount();
    if(sense)
        changed=true;
    while(sense)
    {
        Action *currentWidget=top.getCurrent();
        if(sense>0)
        {
            currentWidget->turnLeft();
            sense--;
        }else
        {
            currentWidget->turnRight();
            sense++;            
        }
    }
    if(changed)
    {
        updateScreenAndGen();
        changed=false;
    }    
    pushButton->run();
    if(pushButton->pressed())
    {
        Action *currentWidget=top.getCurrent();
        currentWidget->shortPress();
        updateScreenAndGen();
    }
}

// eof

