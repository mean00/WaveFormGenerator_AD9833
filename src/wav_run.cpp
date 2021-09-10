
#include "lnArduino.h"
#include "RotaryEncoder.h"
#include "wav_run.h"
/**
 */
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
}
/**
 * 
 * @return 
 */
int  getFrequency()
{
    int fq=(hiDigit.getIndex()*10+loDigit.getIndex());
    int s=scaleDigit.getIndex();
    for(int i=0;i<s;i++)
    {
        fq*=10;
    }
    fq/=10;
    if(!fq) fq=1;
    return fq;
}

/**
 * 
 * @return 
 */
extern WaveForm  getWaveForm()
{
    return (WaveForm)waveForm.getIndex();
}
/**
 * 
 * @param event
 */
bool runLoop(  lnRotary::EVENTS  event,int count)
{    
    bool dirty=false;
    
    if(event==lnRotary::EVENT_NONE) return false;
    
    if(event & lnRotary::ROTARY_CHANGE)
    {
        dirty=true;
        while(count)
        {
            Action *currentWidget=top.getCurrent();
            if(count>0)
            {
                currentWidget->turnLeft();
                count--;
            }else
            {
                currentWidget->turnRight();
                count++;            
            }
        }
    }
    if(event & lnRotary::SHORT_PRESS)
    {
            Action *currentWidget=top.getCurrent();
            currentWidget->shortPress();
            dirty=true;
    }
    return dirty;
}

// eof

