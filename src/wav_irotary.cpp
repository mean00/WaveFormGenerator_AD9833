
#include "Rotary.h"
#include "wav_irotary.h"

static WavRotary *current=NULL;

/**
 */
 WavRotary::WavRotary(int pinA,int pinB ) : _rotary(pinA,pinB)
 {
    current=this;
    _count=0;
    PCICR |= (1 << PCIE2);
    PCMSK2 |= (1 << pinA) | (1 << pinB); // only works for up to 7!
    _rotary.begin(true);
    interrupts();
 }
 int          WavRotary::getCount()
 {
     noInterrupts();
     int c=_count;
     _count=0;
     interrupts();
     return c;
 }
 /**
  */
 
ISR(PCINT2_vect) 
{
  if(!current) return;
  current->interrupt();
}
 
 /**
  */
 void WavRotary::interrupt()
 {
     switch(_rotary.process())
     {
        case DIR_CCW:  _count++;break;
        case DIR_CW:   _count--;break;
        default:       break;
     }
 }

 // EOF
