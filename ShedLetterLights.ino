#include "NetworkServices.h"
#include "LightsService.h"
#include "WebServer.h"

void setup()
{
  setupSerialCommunications();
  debugln("Starting Setup");

  networkServices.connect();
  webServer.startHttpListener();
  lightsService.configureRGBLightStrip();

  debugln("Setup Completed");
}

void loop()
{
  if (networkServices.isConnected())
  {
    webServer.listenForHttpRequest();
  }
  else
  {
    networkServices.connect();
  }

  lightsService.showLightsPattern();
}

void setupSerialCommunications()
{
  if (DEBUG == 1)
  {
      // Open serial communications and wait for port to open:
      Serial.begin(115200);
  }
}
