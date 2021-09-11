/**
 
 */
#pragma once
#include "lnArduino.h"
#include "libraries/simplerSSD1306/ssd1306_base.h"

/**
 * 
 */
class WavDisplay
{
public:
  
    WavDisplay(OLEDCore *s);
    /**
     */
    ~WavDisplay()
    {
      
    }
    void drawTab(int tab);
    void drawDigit(int column, int value,bool highlight);
    void displayWaveForme(int waveForme,bool hilight);
    void drawFrequency(const char *fq);
    OLEDCore *_ssd;     
};

// EOF
