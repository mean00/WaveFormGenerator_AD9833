//
//

#include "lnArduino.h"
#include "lnSPI.h"
#include "simplerAD9833.h"
#include "libraries/simplerAD9833/simplerAD9833.h"

#include "RotaryEncoder.h"

#include "libraries/simplerSSD1306/ssd1306_i2c_lnGd32vf103.h" // works also with gd32f1/Stm32f1
#include "FreeSans7pt7b.h"

#include "wavePinout.h"
#include "wav_run.h"
simplerAD9833 *ad;
OLED_lnGd32 *ssd1306;
lnRotary *rotary;


void amp(bool onoff)
{
    digitalWrite(AD9833_AMP, onoff);
}

/**
 * 
 */
void setup()
{
    pinMode(LN_SYSTEM_LED,OUTPUT);    
    pinMode(AD9833_AMP,OUTPUT);    
    
    // ad9833
    
    digitalWrite(LN_SYSTEM_LED,0);
    Logger("Starting AD9833...");
    hwlnSPIClass *spi=new hwlnSPIClass(AD9833_SPI);
    ad=new simplerAD9833(spi,AD9833_CS);
    
    // ssd now
    lnI2C *i2c=new lnI2C(SSD1306_I2C,SSD1306_SPEED);
    i2c->begin(SSD1306_ADR);
    ssd1306=new OLED_lnGd32( *i2c, -1);
    ssd1306->begin();
    ssd1306->setFontFamily(&FreeSans7pt7b,&FreeSans7pt7b,&FreeSans7pt7b);
    ssd1306->setFontSize(OLEDCore::SmallFont);

    // rotary
    rotary=new lnRotary(ROTARY_PUSH,ROTARY_LEFT,ROTARY_RIGHT);    
    initLoop();
}
/**
 * 
 */
void redraw()
{
    
}

void loop()
{
    Logger("Entering main app...\n");
    int onoff=0;
    //
    ssd1306->clrScr();
    ssd1306->update();

    
    // use safe default
    ad->setFrequency(10*1000);
    ad->setWaveForm(simplerAD9833::Sine);
    amp(true);
    ad->enable();
    
    rotary->start();
    redraw();
    while(1)
    {
       lnRotary::EVENTS  event=rotary->waitForEvent(1000);
       int count=rotary->getCount();
       if(event)
       {
            if(runLoop(event,count))
            {
                redraw();
            }
       }
    }
   
}
// EOF
