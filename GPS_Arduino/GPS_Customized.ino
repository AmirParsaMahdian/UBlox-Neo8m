//This is a customized version of "full example" in TinyGPS++ library
//for sadra cansat team 2017

#include <TinyGPS++.h>
#include <SoftwareSerial.h>

static const int RXPin = 3, TXPin = 4;
static const uint32_t GPSBaud = 9600;

TinyGPSPlus gps;
SoftwareSerial ss(RXPin, TXPin);

void setup()
{
  Serial.begin(115200);
  ss.begin(GPSBaud);
}

void loop()
{
    if(gps.satellites.isValid())
    {
      Serial.print("Number of available satellites: ");
      Serial.println(gps.satellites.value());
    }
  else
    Serial.println("no data available for GPS lock");
    
    if(gps.location.isValid())
    {
      Serial.print("Location: ");
      printFloat(gps.location.lat());
      Serial.print(" / ");
      printFloat(gps.location.lng());
      Serial.println();
    }
  else
    Serial.println("No Location available");
 
  if(gps.altitude.isValid())
    {
      Serial.print("Altitude: ");
      Serial.println(gps.altitude.meters());
    }
  else  
    Serial.println("no data available for altitude");
 
  if(gps.speed.isValid())
    {
      Serial.print("Speed: ");
      Serial.println(gps.speed.kmph());
    }
  else
    Serial.println("no data available for speed");

  Serial.println("********************************");
  
 smartDelay(1000);

}

// This custom version of delay() ensures that the gps object
// is being "fed".
static void smartDelay(unsigned long ms)
{
  unsigned long start = millis();
  do 
  {
    while (ss.available())
      gps.encode(ss.read());
  } while (millis() - start < ms);
}

static void printFloat(float val)
{
  
    Serial.print(val, 6);
    int vi = abs((int)val);
    int flen = 6 + (val < 0.0 ? 2 : 1); // . and -
    flen += vi >= 1000 ? 4 : vi >= 100 ? 3 : vi >= 10 ? 2 : 1;
    for (int i=flen; i<11; ++i)
      Serial.print(' ');
  
  smartDelay(0);
}

