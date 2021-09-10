/**
 */
class Timer
{
public:
    double zero;
    double next;
    int    _period;
    Timer(int p)
    {
      _period=p;
      reset();  
    }
    void reset(void)
    {
      zero=millis();
      next=_period;
    }
    bool rdv(void)
    {
      double now=millis()-zero;
      if(now>next)
      {
        return true;
      }
      return false;
    }
    bool nextPeriod()
    {
      next+=_period;
      return true;
    }
    double period()
    {
      return (double)_period;
    }
    void wallClock(int &mm, int &ss)
    
    {
        double m=(millis()-zero)/1000.; // seconds        
        mm= (int)(m/60.);
        ss= (int)(m-mm*60);
    }
    int elapsed()
    {
      return (millis()-zero)/1000;
    }
    
};
