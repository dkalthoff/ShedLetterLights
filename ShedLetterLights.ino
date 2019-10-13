#include "LightsPattern.h"

lightsPatternEnum currentLightsPattern = randomPulse;
bool lightAreOn = true;

byte selectedPulseRed = 0xff;
byte selectedPulseGreen = 0xff;
byte selectedPulseBlue = 0xff;
String selectedPulseColor = "#ff0000";

byte selectedStaticRed = 0xff;
byte selectedStaticGreen = 0xff;
byte selectedStaticBlue = 0xff;
String selectedStaticColor = "#ff0000";

byte selectedSegmentsRed1 = 0xff;
byte selectedSegmentsGreen1 = 0xff;
byte selectedSegmentsBlue1 = 0xff;
String selectedSegmentsColor1 = "#ff0000";
byte selectedSegmentsRed2 = 0xff;
byte selectedSegmentsGreen2 = 0xff;
byte selectedSegmentsBlue2 = 0xff;
String selectedSegmentsColor2 = "#ff0000";
byte selectedSegmentsRed3 = 0xff;
byte selectedSegmentsGreen3 = 0xff;
byte selectedSegmentsBlue3 = 0xff;
String selectedSegmentsColor3 = "#ff0000";

void setup() 
{  
  Serial.begin(115200);
  delay( 3000 ); // power-up safety delay

  Serial.println("Starting Setup");
  connectToWiFi();
  setDateTime();
  startHttpListener();
  configureRGBLightStrip();
  Serial.println("Setup Completed");
}

void loop() 
{
  listenForHttpRequest();
}
