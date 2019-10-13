/*************************************************
  Start an UDP connection to get the time in unix,
  then set the real time clock (rtc)
 ************************************************/
#include <SPI.h>
#include <WiFi101.h>
#include <WiFiUdp.h>
#include <RTCZero.h>
#include <Dusk2Dawn.h>
#include <RTClib.h> //https://github.com/adafruit/RTClib

RTCZero rtc;

const int CST = 5*60*60; //change this to adapt it to your time zone   hours*minutes*seconds
Dusk2Dawn myDusk2DawnLocation(45.673504, -94.549025, -5);
byte cachedDay = 0;
int sunsetUnixTime = 0;
bool shouldOverrideSunset = false;

void setDateTime() 
{  
  rtc.begin();

  unsigned long epoch;
  int numberOfTries = 0, maxTries = 6;
  Serial.println("Fetching time from NTP Server");
  do 
  {
    epoch = WiFi.getTime();
    numberOfTries++;
    Serial.print("Try #" + String(numberOfTries) + " Epoch received: ");
    Serial.println(epoch);
    if(epoch == 0)
    {
      Serial.println("Retry in 3 seconds");
      delay( 3000 );
    }
  }
  while ((epoch == 0) && (numberOfTries < maxTries));

  if (epoch == 0 && numberOfTries >= maxTries) 
  {
    Serial.println("NTP server unreachable!! Retry in 30 seconds");
    delay( 30000 ); // pause for 30 seconds before trying again
    setDateTime();
  }
  else 
  {
    Serial.println("NTP server reached");

    epoch = epoch - CST; // Adjust to central standard time
    Serial.print("Epoch adjusted to CST: ");
    Serial.println(epoch);
    rtc.setEpoch(epoch);

    Serial.print("Current CST Time: ");
    printDateTime();
    Serial.println("Today's sunrise is at " + getSunriseAsString());
    Serial.println("Today's sunset is at " + getSunsetAsString());
  }
}

int getSunrise()
{
  return myDusk2DawnLocation.sunrise(rtc.getYear(), rtc.getMonth(), rtc.getDay(), false);
}

String getSunriseAsString()
{
  char timeMySunrise[] = "00:00";
  Dusk2Dawn::min2str(timeMySunrise, getSunrise());
  return String(timeMySunrise) + "am";
}

int getSunset()
{
  int sunSetInMinutes = myDusk2DawnLocation.sunset(rtc.getYear(), rtc.getMonth(), rtc.getDay(), false);
}

String getSunsetAsString()
{
  char timeMySunset[] = "00:00";
  int sunSetInMinutes = getSunset();
  Dusk2Dawn::min2str(timeMySunset, sunSetInMinutes - 720);
  return String(timeMySunset) + "pm";
}

bool isAfterSunset()
{
  if(rtc.getDay() != cachedDay)
  {
    float floatHour   = getSunset() / 60.0;
    float floatMinute = 60.0 * (floatHour - floor(floatHour));
    byte  byteHour    = (byte) floatHour;
    byte  byteMinute  = (byte) floatMinute;
    DateTime dateTimeSunset(rtc.getYear(), rtc.getMonth(), rtc.getDay(), byteHour, byteMinute, 0);
    sunsetUnixTime = dateTimeSunset.unixtime();
    Serial.print("Setting cached value for sunset unix time: ");
    Serial.println(sunsetUnixTime);
    
    cachedDay = rtc.getDay();    
    Serial.print("Setting cached value for Day: ");
    Serial.println(cachedDay);
  }
  
  DateTime dateTimeNow(rtc.getYear(), rtc.getMonth(), rtc.getDay(), rtc.getHours(), rtc.getMinutes(), 0);
  
  return dateTimeNow.unixtime() > sunsetUnixTime;
}

void printDateTime() 
{ 
  Serial.println(getDateTimeAsString());
}

String getDateTimeAsString() 
{ 
  return getDateAsString() + " " + getTimeAsString();
}

String getDateAsString()
{
  return get2digits(rtc.getMonth()) + "/" + get2digits(rtc.getDay()) + "/" + get2digits(rtc.getYear()); 
}

String getTimeAsString()
{
  // ...and time
  uint8_t hour = rtc.getHours();
  if (hour > 12) {
    hour = hour - 12;
  }
  return get2digits(hour) + ":" + get2digits(rtc.getMinutes()) + getAMPM();
}

String get2digits(int number) 
{
  if (number < 10) {
    return "0" + String(number);
  }
  return String(number);
}

String getAMPM()
{
  if(rtc.getHours() < 12)
  {
    return "AM";
  }
  else
  {
    return "PM";
  }
}
