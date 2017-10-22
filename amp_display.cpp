/***************************************************************************
  
 ***************************************************************************/

#include <Wire.h>
#include <SPI.h>
#include "amp_display.h"


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
 ampDisplay::ampDisplay() :   u8g(8,9,10) // cs a0 rst
{
    //https://github.com/olikraus/u8glib/wiki/fontsize
    u8g.firstPage();  
    do
    {    
    u8g.setFont(u8g_font_ncenB24);
    u8g.drawStr(0, 32, "Q Meter.1");
#if 0
    u8g.setFont(u8g_font_7x13B);
    u8g.drawStr(1, 64-10, "DICHARG   000:00 s");
    u8g.drawStr(1, 64,    "1234 mA    9876 mV");    
#endif    

    }
    while(u8g.nextPage());  
    //delay(3000);
}


/**
 * 
 */
void ampDisplay::displayInfo(float current,float busVoltage,double Q ,int mn,int sec)
{
  char stA[80];
  char stB[80];
  char stC[80];

  int mv=busVoltage*1000; 
  
  //Serial.println(Q);
  double qq=Q;
  qq=(qq)/(3600.*1000.);
  
  int q=(int)qq;
  sprintf(stA,"Q:%04d",q);
  sprintf(stB,"%04d mV    %04d mA",mv,(int)current);
  
  sprintf(stC,"DIS  %02d  %03d:%02d s",getPercentFromVoltage(mv),mn,sec);
  
  
  u8g.firstPage();  
    do
    {    
    u8g.setFont(u8g_font_ncenB24);
    u8g.drawStr(0, 32, stA);
    u8g.setFont(u8g_font_7x13B);
    u8g.drawStr(1, 64-10, stB);
    u8g.drawStr(1, 64,    stC);    

    }
    while(u8g.nextPage());
  
}


/**
 * 
 */
void ampDisplay::displayChargeInfo(float current,float busVoltage,double Q ,int mn,int sec)
{ 
  char stA[80];
  char stB[80];
  char stC[80];

  int mv=busVoltage*1000; 
  
  //Serial.println(Q);
  double qq=Q;
  qq=(qq)/(3600.*1000.);
  
  int q=(int)qq;
  sprintf(stA,"C:%04d",q);
  sprintf(stB,"%04d mV CHARGE=%02d%%",mv,getPercentFromVoltage(mv));   
  sprintf(stC,"Took %d mn",mn);
  
  
  u8g.firstPage();  
    do
    {    
    u8g.setFont(u8g_font_ncenB24);
    u8g.drawStr(0, 32, stA);
    u8g.setFont(u8g_font_7x13B);
    u8g.drawStr(1, 64-10, stB);
    u8g.drawStr(1, 64,    stC);    

    }
    while(u8g.nextPage());
  
}
/**
 * 
 */
int getPercentFromVoltage(int mv)
{
   if(mv>3870) return 90;
   if(mv>3756) return 80;
   if(mv>3652) return 70;
   if(mv>3560) return 60;
   if(mv>3700) return 50;
   if(mv>3440) return 40;
   if(mv>3408) return 30;
   if(mv>3368) return 20;
   if(mv>3308) return 10;
   
   return 5;
}
/**
 * 
 * @param st
 */
void ampDisplay::displayStatus(const char *st)
{
  u8g.firstPage();  
  do
  {
    u8g.drawStr(16, 52, st);
  }
  while(u8g.nextPage());  
}
/**
 * 
 * @param c
 */
void ampDisplay::displayCurrent(float c)
{
  char st[128];
  sprintf(st,"%d mA",(int)c);
  u8g.firstPage();  
  do
  {
    u8g.drawStr(16, 52, st);
  }
  while(u8g.nextPage());  
}
/**
 * 
 * @param one
 * @param two
 */
void ampDisplay::displayWarning(const char *one, const char *two)
{
  u8g.setFont(u8g_font_7x13B);
  u8g.firstPage();  
  do
  {
    u8g.drawStr(1, 32, "/!\\");      
    u8g.drawStr(24, 32, one);
    u8g.drawStr(24, 32+28*1, two);
  }
  while(u8g.nextPage());      
}


/**
 * 
 */
void ampDisplay::displayDone(double Q,int totalTimeMinute)
{
  char stA[80];
  char stB[80];

  double qq=Q;
  qq=(qq)/(3600.*1000.);
  
  int q=(int)qq;
  sprintf(stA,"Cap :%04dmah",q);
  sprintf(stB,"Done (%03dmn)",totalTimeMinute);
  u8g.firstPage();
  do
  {
    u8g.drawStr(16, 12, stB);
    u8g.drawStr(16, 32, stA);
  }
  while(u8g.nextPage());  
}
// EOF

