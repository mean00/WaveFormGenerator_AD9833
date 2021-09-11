/***************************************************************************
  
 ***************************************************************************/

#include "wav_display.h"
/**
 * 
 * @param s
 */
  WavDisplay::WavDisplay(OLEDCore *s)
  {
      _ssd=s;
  }


static const  int sinus[]={0,6,12,16,20,23,24,23,20,16,11,6,0,-6,-12,-16,-20,-23,-24,-23,-20,-16,-11,-6};
/**
 * \fn displayWaveForme
 */
void WavDisplay::displayWaveForme(int waveForme,bool highligh)
{
    int x=2;
    int y=16;
#define WIDTH  24    
#define HEIGHT 24
   
    if(highligh)
    {
        _ssd->square(x-2,y-4,
                WIDTH+4,HEIGHT*2+4,1);
    }
    
    switch(waveForme)
    {
        case 0 :  //sine
            if(highligh)
            for(int i=0;i<WIDTH;i++)
                _ssd->clrPixel(x+i,y+sinus[i]/2+HEIGHT/2)   ;                             
            else
            for(int i=0;i<WIDTH;i++)
                _ssd->setPixel(x+i,y+sinus[i]/2+HEIGHT/2)   ;             
            break;
        case 2 :  //square
            if(highligh)
            {
            _ssd->clrRect(x,y,x+WIDTH/2,y);
            _ssd->clrRect(x+WIDTH/2,y,x+WIDTH/2,y+WIDTH);
            _ssd->clrRect(x+WIDTH/2,y+WIDTH,x+WIDTH,y+WIDTH);
            _ssd->clrRect(x+WIDTH,y+WIDTH,x+WIDTH, y+WIDTH);                
                
            }else
            {
            _ssd->drawRect(x,y,x+WIDTH/2,y);
            _ssd->drawRect(x+WIDTH/2,y,x+WIDTH/2,y+WIDTH);
            _ssd->drawRect(x+WIDTH/2,y+WIDTH,x+WIDTH,y+WIDTH);
            _ssd->drawRect(x+WIDTH,y+WIDTH,x+WIDTH, y+WIDTH);
            }
            break;
        case 1 :  // Triangle
            if(highligh)
            {
                _ssd->clrLine(x+0,y,x+WIDTH/2,y+WIDTH);
                _ssd->clrLine(x+WIDTH/2,y+WIDTH,x+WIDTH,y);
            }else
            {
                _ssd->drawLine(x+0,y,x+WIDTH/2,y+WIDTH);
                _ssd->drawLine(x+WIDTH/2,y+WIDTH,x+WIDTH,y);
            }
            break;
    default:
        break;
    }
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
void WavDisplay::drawTab(int tab )
{
#define NEXT 32
#define TABW 24
#define TABH 2
    int x=2+tab*NEXT;
    int y=60;
    _ssd->drawRect(x,y,x+TABW,y+TABH);
}
void WavDisplay::drawDigit(int column, int value, bool hilight)
{
    char p[2]={0,0};    
    p[0]='0'+value;
    _ssd->setFontSize(OLEDCore::MediumFont);
    _ssd->myDrawChar(32+32*column,48,p[0],hilight);    
}
/**
 * 
 * @param fq
 */
void WavDisplay::drawFrequency(const char *fq)
{
    _ssd->setFontSize(OLEDCore::SmallFont);
    int n=strlen(fq);
    _ssd->print(96-n*8,63,fq);
}

// EOF

