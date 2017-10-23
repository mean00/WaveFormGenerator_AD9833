/**
 
 */
#pragma once
#include <U8glib.h>

/**
 * 
 */
class WavDisplay
{
public:
  /**
   */
  
     /* Create an instance for the SSD1306 OLED display in SPI mode 
     * connection scheme: 
     *   D0=sck=Pin 12 
     *   D1=mosi=Pin 11 
     *   CS=Pin 8 
     *   DC=A0=Pin 9
     *   Reset=Pin 10
  */
  
    WavDisplay();
    /**
     */
    ~WavDisplay()
    {
      
    }
    void displayStatus      (const char *st);
    void update         (int waveForm, int hiDigit, int lowDigit, float fq);

protected:
    U8GLIB_SSD1306_128X64 u8g;
  
};

// EOF
