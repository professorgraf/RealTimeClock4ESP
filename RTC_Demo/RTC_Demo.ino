/*****************
 * Real time clock demonstration project
 * 
 * RealTimeClock4ESP
 * 
 * 2022-03-19 by Prof. Dr. Markus Graf
 * This code is provided on an as-is base
 * under the GLPL v3 license
 */
#include <Wire.h>
#include <Time.h>
#include <RTClib.h>

// mit der RTC zu verbinden (über I2C TwoWire, PCF8563 chip)
RTC_PCF8563 theClock;
TwoWire wire;

// timer, keeps track within the loop in order to 
long ms;

void setup()
{
  Serial.begin(115200);
  wire.begin( 5, 4 );   // D1 =5, D2 = 4
  theClock.begin( &wire );

  Serial.println();
  if ( theClock.isrunning() )
  {
    Serial.println("RTC is up and running");
  }
  else
  {
    Serial.println("RTC is not working");
  }

  if ( theClock.lostPower() )
  {
    Serial.println("RTC not initialized.");
    theClock.adjust( DateTime(F(__DATE__), F(__TIME__)) );
  }

  ms = millis();
}

// repeatedly go through this code and every second update the time (and send it to the Monitor for info)
// please modify for the project
void loop()
{
  if ( millis() - ms > 1000 )  
  {
    DateTime tm = theClock.now();
    Serial.println( tm.timestamp() );
    ms = millis();
  }
}
