/**
 
 */
#pragma once
#include "U8glib.h"

/**
 * 
 */
class ampDisplay
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
  
    ampDisplay();
    /**
     */
    ~ampDisplay()
    {
      
    }
    void displayStatus      (const char *st);
    void displayCurrent     (float c);
    void displayWarning     (const char *one, const char *two);
    void displayInfo        (float current,float busVoltage,double Q,int mn,int sec);
    void displayChargeInfo  (float current,float busVoltage,double Q,int mn,int sec);
    void displayDone        (double Q,int totalTimeMinute);

protected:
    U8GLIB_SSD1306_128X64 u8g;
  
};

// EOF
