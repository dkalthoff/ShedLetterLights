#ifndef LightsService_h
#define LightsService_h

#define FASTLED_INTERNAL
#include <FastLED.h>
#include <FlashStorage.h>
#include "LightsConstants.h"
#include "LightsPattern_Scenes.h"
#include "LightsPattern_SelectedStatic.h"

FlashStorage(lightsConfigurationStored, LightsConfiguration);

class LightsService
{
  private:
    bool lightsAreCleared = false;

  public:
    void configureRGBLightStrip()
    {
      randomSeed(analogRead(0)); // seed the random generator

      FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
      FastLED.setBrightness(BRIGHTNESS);

      debugln("RGB Light Strip Configured");

      // Note: the area of flash memory reserved lost every time
      // the sketch is uploaded on the board.
      LightsConfiguration lightsConfiguration = lightsConfigurationStored.read();
      if (!lightsConfiguration.isValid)
      {
        lightsConfiguration.isValid = true;
        lightsConfiguration.lightsPattern = scenes;
        lightsConfiguration.scenesType = rainbow;
        lightsConfigurationStored.write(lightsConfiguration);
        debugln("Lights configuration defaults stored in flash storage");
      }
    }

    void showLightsPattern()
    {
      LightsConfiguration lightsConfiguration = lightsConfigurationStored.read();

      switch (lightsConfiguration.lightsPattern)
      {
        case scenes:
          lightsPattern_Scenes.show(lightsConfiguration.scenesType);
          break;
        case selectedStatic:
          lightsPattern_SelectedStatic.show(lightsConfiguration.colors[0]);
          break;
      }
    }

    void setLightsPattern(LightsConfiguration &lightsConfiguration)
    {
      bool lightsConfigurationHasChanged = false;
      LightsConfiguration storedLightsConfiguration = lightsConfigurationStored.read();

      switch (lightsConfiguration.lightsPattern)
      {
        case scenes:
          if (lightsConfiguration.lightsPattern != storedLightsConfiguration.lightsPattern || lightsConfiguration.scenesType != storedLightsConfiguration.scenesType)
          {
            lightsConfigurationHasChanged = true;
            debug("Scene changed to ");
            debugln(getScenesType(lightsConfiguration.scenesType));
          }
          break;
        case selectedStatic:
          debug("Set static color: ");
          debugln(lightsConfiguration.colors[0]);
          debug("Stored static color: ");
          debugln(storedLightsConfiguration.colors[0]);
          
          if(strcmp(lightsConfiguration.colors[0], storedLightsConfiguration.colors[0]) != 0)
          {
            lightsConfigurationHasChanged = true;
          }
          break;
      }

      if (lightsConfigurationHasChanged)
      {
        lightsConfigurationStored.write(lightsConfiguration);
        debugln("The changed lights configuration written to flash storage");
      }
    }
};

LightsService lightsService;

#endif
