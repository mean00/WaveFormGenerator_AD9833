/***************************************************************************
  
 ***************************************************************************/
#include <Wire.h>
#include "wav_display.h"


static int getPercentFromVoltage(int mv);
// mosi=11
// miso=12
// sck=13
// oled
/*
 *   D0=sck= Pin 13  D13
 *   D1=mosi=Pin 11  D11
 *   CS=     Pin 8 
 *   DC=A0=  Pin 9
 *   Reset=  Pin 10
*/
//
// u8g(U8G2_R0,8,9,10)
 WavDisplay::WavDisplay(int cs, int ds, int rst) :   u8g(U8G2_R0,cs,ds,rst) // cs a0 rst  *rotation, uint8_t cs, uint8_t dc, uint8_t reset
{    
    u8g.begin();
    //u8g.setFont(u8g_font_7x13B);
    u8g.setFont(u8g_font_ncenB24);
    
    u8g.firstPage();  
    do
    {        
      u8g.drawStr(0, 32, "Generator");
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
 
    u8g.drawStr(64, 52, st);
}

/**
 */
void WavDisplay::startRefresh()
{
      
}
void WavDisplay::endRefresh()
{
   
}
/**
 * 
 * @param topIndex
 * @param topSelection
 * @param waveform
 * @param hidigit
 * @param lodigit
 * @param scaledigit
 */

void WavDisplay::drawDigit(int column, int value)
{
    char p[2]={0,0};    
    p[0]='0'+value;
    u8g.drawStr(column+4,24+4,p);
    
}
/**
 * 
 * @param topIndex
 * @param topSelection
 * @param waveform
 * @param hidigit
 * @param lodigit
 * @param scaledigit
 */
void WavDisplay::draw(int topIndex, int topSelection, int waveform, int hidigit, int lodigit, int scaledigit,const char *dis)
{
    u8g.setColorIndex(1);
    u8g.firstPage(); 
    
    float fq=(hidigit*10+lodigit); // 00--99
    
    do
    {
        u8g.setFont(u8g_font_ncenB24);
        drawDigit(28,hidigit);
        drawDigit(28*2,lodigit);
        drawDigit(28*3,scaledigit);
        displayWaveForme(2,24,waveform);
        u8g.drawHLine(0+topIndex*28,0,28);
        u8g.drawHLine(0+topIndex*28,1,28);
        if(topSelection)
        {
                u8g.drawHLine(0+topIndex*28,60,28);
                u8g.drawHLine(0+topIndex*28,61,28);
        }
        //u8g.setFont(u8g_font_7x13B);
        u8g.setFont(u8g2_font_inb16_mf);
        u8g.drawStr(24+4,48+4,dis);
    }
    while(u8g.nextPage());
}

static const  int sinus[]={0,6,12,16,20,23,24,23,20,16,11,6,0,-6,-12,-16,-20,-23,-24,-23,-20,-16,-11,-6};

    

/**
 * \fn displayWaveForme
 */
void WavDisplay::displayWaveForme(int x,int y,int waveForme)
{
    
#define WIDTH  24    
#define HEIGHT 24
   
    
    
    switch(waveForme)
    {
        case 0 :  //sine
            for(int i=0;i<WIDTH;i++)
                u8g.drawPixel(x+i,y+sinus[i]+HEIGHT/2);
            break;
        case 2 :  //square
            u8g.drawHLine(x+0,y+0,WIDTH/2);
            u8g.drawVLine(x+WIDTH/2,y,WIDTH);
            u8g.drawHLine(x+WIDTH/2,y+WIDTH,WIDTH/2);
            break;
        case 1 :  // Triangle
            u8g.drawLine(x+0,y+WIDTH,x+WIDTH/2,y);
            u8g.drawLine(x+WIDTH/2,y,x+WIDTH,y+WIDTH);
            
            break;
    default:
        break;
    }
   
}

// EOF

