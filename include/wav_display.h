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
    void drawDigit(int column, int value);
    void displayWaveForme(int waveForme);
    void drawFrequency(const char *fq);
    OLEDCore *_ssd;     
};

// EOF
