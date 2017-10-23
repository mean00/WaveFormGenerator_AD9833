/***************************************************************************
  
 ***************************************************************************/

#include <Wire.h>
#include <SPI.h>
#include "wav_display.h"


static int getPercentFromVoltage(int mv);
// mosi=11
// miso=12
// sck=13
// oled
/*
 *   D0=sck=Pin 13 
 *   D1=mosi=Pin 11 
 *   CS=Pin 8 
 *   DC=A0=Pin 9
 *   Reset=Pin 10
*/
//
 WavDisplay::WavDisplay() :   u8g(8,9,10) // cs a0 rst
{
    //https://github.com/olikraus/u8glib/wiki/fontsize
    u8g.firstPage();  
    do
    {    
    u8g.setFont(u8g_font_ncenB24);
    u8g.drawStr(0, 32, "WaveForm");
    }
    while(u8g.nextPage());  
}
#if 0
    u8g.setFont(u8g_font_ncenB24);
    u8g.drawStr(0, 32, stA);
    u8g.setFont(u8g_font_7x13B);
    u8g.drawStr(1, 64-10, stB);
    u8g.drawStr(1, 64,    stC);    
#endif

/**
 * 
 * @param st
 */
void WavDisplay::displayStatus(const char *st)
{
  u8g.firstPage();  
  do
  {
    u8g.drawStr(16, 52, st);
  }
  while(u8g.nextPage());  
}
// EOF

