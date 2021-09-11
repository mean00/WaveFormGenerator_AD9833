
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
                 Action(Selection s) {_selection=s;}
    virtual void turnLeft()=0;
    virtual void turnRight()=0;
    virtual void shortPress()=0;
    virtual void setParent(Action *a) {}
    
    Selection _selection;
};
/**
 */
class TopAction : public Action
{
public:
    TopAction() : Action(TOP_SELECTION)
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
    DigitAction(int mx, Selection s) : Action(s)
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


/**
 * 
 */
class ActionInterfaceImpl: public ActionInterface
{
public:
            ActionInterfaceImpl();
    virtual ~ActionInterfaceImpl() {}
    virtual int getFrequency();
    virtual void getFrequencyAsString(char *out, int maxSize);
    virtual int getNumber(int rank);
    virtual bool run(lnRotary::EVENTS  event,int ticks);
    virtual WaveForm getWaveForm();
    virtual Selection selection()
    {
        Action *current=top.getCurrent();
        return current->_selection;
    }
    virtual int selectionIndex()
    {
        return top.getIndex();
    }
protected:
    TopAction   top;
    DigitAction waveForm;
    DigitAction hiDigit;
    DigitAction loDigit;
    DigitAction scaleDigit;
    
};
/**
 * 
 * @return 
 */
ActionInterface *createActionInterface()
{
    return new ActionInterfaceImpl;
    
    
}

/**
 * 
 */
ActionInterfaceImpl::ActionInterfaceImpl() :  waveForm(3,WAVEFORM_SELECTION),  hiDigit(10,HIDIGIT_SELECTION),    loDigit(10,LODIGIT_SELECTION),   scaleDigit(7,SCALE_SELECTION)
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
 * @param rank
 * @return 
 */
int ActionInterfaceImpl::getNumber(int rank)
{
    switch(rank)
    {
        case 0: return hiDigit.getIndex();break;
        case 1: return loDigit.getIndex();break;
        case 2: return scaleDigit.getIndex();break;
        default: xAssert(0);return 0;break;
    }
}
/**
 * 
 * @return 
 */
int  ActionInterfaceImpl::getFrequency()
{
    int fq=(hiDigit.getIndex()*10+loDigit.getIndex());
    int s=scaleDigit.getIndex();
    for(int i=0;i<s;i++)
    {
        fq*=10;
    }   
    if(!fq) fq=1;
    return fq;
}

/**
 * 
 * @return 
 */
WaveForm  ActionInterfaceImpl::getWaveForm()
{
    return (WaveForm)waveForm.getIndex();
}
/**
 * 
 * @param fq
 */

const char scaleChar[4]={' ','k','M','G'};

void ActionInterfaceImpl::getFrequencyAsString(char *tmp, int maxSize)
{
    int scale=scaleDigit.getIndex();
    int r=scale%3;
    int t=(scale-r)/3;
    
    int  f=(hiDigit.getIndex()*10)+loDigit.getIndex();
    for(int i=0;i<r;i++) f=f*10.;
    if(f>=1000)
    {
        t++;
        int q=(f/100)%10;
        int p=f/1000;
        snprintf(tmp,maxSize,"%d.%d%cHz",p,q,scaleChar[t]);
    }else
    {
        snprintf(tmp,maxSize,"%d%cHz",f,scaleChar[t]);
    }
 //   std::string str=std::string(tmp);       
}

/**
 * 
 * @param event
 */
bool ActionInterfaceImpl::run(  lnRotary::EVENTS  event,int count)
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

// EOF

