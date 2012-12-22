#include <SPI.h>        //SPI.h must be included as DMD is written by SPI (the IDE complains otherwise)
#include <DMD.h>        //
#include <TimerOne.h>   //
#include "SystemFont5x7.h"
#include "Arial_black_16.h"

#define DISPLAYS_ACROSS 2
#define DISPLAYS_DOWN 1
DMD dmd(DISPLAYS_ACROSS, DISPLAYS_DOWN);

#include "DHT.h"
#define DHTPIN 2     // what pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302)
DHT dht(DHTPIN, DHTTYPE);

void ScanDMD()
{ 
  dmd.scanDisplayBySPI();
}

void setup(void)
{
  Serial.begin(38400);
  dht.begin();  
  
  //initialize TimerOne's interrupt/CPU usage used to scan and refresh the display
  Timer1.initialize( 5000 );           //period in microseconds to call ScanDMD. Anything longer than 5000 (5ms) and you can see flicker.
  Timer1.attachInterrupt( ScanDMD );   //attach the Timer1 interrupt to ScanDMD which goes to dmd.scanDisplayBySPI()

  //clear/init the DMD pixels held in RAM
  dmd.clearScreen( true );   //true is normal (all pixels off), false is negative (all pixels on)

//  stripeChaser();
}

void loop(void)
{
  stats();
  delay(6000);
  message();
}

void message(void) {
  dmd.clearScreen( true );
  dmd.selectFont(Arial_Black_16);

  dmd.drawMarquee("Gold Coast TechSpace",20,63,0);
//  dmd.drawMarquee("Happy Birthday Laura!!! :-)",28,63,0);

  long start=millis();
  long timer=start;
  boolean ret=false;
  while(!ret){
    if ((timer+30) < millis()) {
      ret=dmd.stepMarquee(-1,0);
      timer=millis();
    }
  }
}

void stats(void) {
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  // check if returns are valid, if they are NaN (not a number) then something went wrong!
  if (isnan(t) || isnan(h)) {
    Serial.println("Failed to read from DHT");
  } else {
    Serial.println(t);
    Serial.println(h);

    // convert float values to text
    char temp[5];
    char humid[5];

    dtostrf(h,4,1,humid);
    dtostrf(t,4,1,temp);

    // display some text
    dmd.clearScreen( true );
    dmd.selectFont(System5x7);
    dmd.drawString(0,0, "temp:", 5, GRAPHICS_NORMAL );
    dmd.drawString(0,9, "humid:", 6, GRAPHICS_NORMAL );
    dmd.drawString(32,0, temp, 4, GRAPHICS_NORMAL );
    dmd.drawString(32,9, humid, 4, GRAPHICS_NORMAL );
    dmd.drawString(59,0, "C", 1, GRAPHICS_NORMAL );
    dmd.drawString(59,9, "%", 1, GRAPHICS_NORMAL );
    dmd.drawBox(55, 0, 57, 2, GRAPHICS_NORMAL );
  }
}

void statsBig(void) {
  dmd.clearScreen( true );
  dmd.selectFont(Arial_Black_16);
  dmd.drawString(0,0, "Temp:", 5, GRAPHICS_NORMAL );
  delay(2000);
  dmd.clearScreen( true );
  dmd.drawString(0,0, "Humid:", 6, GRAPHICS_NORMAL );
  delay(2000);
}


void stripeChaser(void) {
  byte b;
  // stripe chaser
  for( b = 0 ; b < 20 ; b++ )
  {
    dmd.drawTestPattern( (b&1)+PATTERN_STRIPE_0 );
    delay( 100 );      
  }
  delay( 100 );      
}

