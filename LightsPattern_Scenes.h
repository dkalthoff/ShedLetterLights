#ifndef LightsPattern_Scenes_h
#define LightsPattern_Scenes_h

#include <FastLED.h>

class LightsPattern_Scenes
{
  private:
    scenesTypeEnum currentScenesType;
    CRGBPalette16 currentPalette;
    bool currentPaletteHasBeenSet = false;
    TBlendType    currentBlending;

    void FillLEDsFromPaletteColors( uint8_t colorIndex)
    {
      uint8_t brightness = 255;

      for ( int i = 0; i < NUM_LEDS; i++) {
        leds[i] = ColorFromPalette( currentPalette, colorIndex, brightness, currentBlending);
        colorIndex += 3;
      }
    }

    void changeCurrentPalette(scenesTypeEnum changeToSceneType)
    {
      switch (changeToSceneType)
      {
        case avonlakers:
          currentPalette = GetAvonLakersPalette(); currentBlending = LINEARBLEND;
          break;
        case christmas:
          currentPalette = GetChristmasPalette(); currentBlending = NOBLEND;
          break;
        case easter:
          currentPalette = GetEasterPalette(); currentBlending = NOBLEND;
          break;
        case forest:
          currentPalette = ForestColors_p; currentBlending = NOBLEND;
          break;
        case heat:
          currentPalette = HeatColors_p; currentBlending = NOBLEND;
          break;
        case lava:
          currentPalette = LavaColors_p; currentBlending = NOBLEND;
          break;
        case ocean:
          currentPalette = OceanColors_p; currentBlending = NOBLEND;
          break;
        case party:
          currentPalette = PartyColors_p; currentBlending = NOBLEND;
          break;
        case patriotic:
          currentPalette = GetPatrioticPalette(); currentBlending = NOBLEND;
          break;
        case purplepride:
          currentPalette = GetAHSPalette(); currentBlending = LINEARBLEND;
          break;
        case rainbow:
          currentPalette = RainbowColors_p; currentBlending = LINEARBLEND;
          break;
        case randomDraw:
          setupTotallyRandomPalette();
          break;
        case valentines:
          currentPalette = GetValentinesPalette(); currentBlending = LINEARBLEND;
          break;
      }
    }

    // This function fills the palette with totally random colors.
    void setupTotallyRandomPalette()
    {
      uint8_t secondHand = (millis() / 1000) % 60;
      static uint8_t lastSecond = 99;

      if (lastSecond != secondHand)
      {
        lastSecond = secondHand;
        if (secondHand ==  0)
        {
          for ( int i = 0; i < 16; i++) {
            currentPalette[i] = CHSV( random8(), 255, random8());
          }
          currentBlending = LINEARBLEND;
        }
      }
    }

    CRGBPalette16 GetAvonLakersPalette()
    {
      CRGB green  = CRGB::DarkGreen;
      CRGB gold = CRGB::Gold;

      return CRGBPalette16(green,  green,  green,  green,
                           green, green, green,  green,
                           gold,  gold,  gold,  gold,
                           gold, gold, gold,  gold );
    }

    CRGBPalette16 GetAHSPalette()
    {
      CRGB purple = CHSV( HUE_PURPLE, 255, 255);
      CRGB white  = CRGB::Gray;

      return CRGBPalette16(white,  white,  white, white,
                           purple, purple, purple, purple,
                           white,  white,  white, white,
                           purple, purple, purple, purple );
    }

    CRGBPalette16 GetChristmasPalette()
    {
      CRGB red = CRGB::Red;
      CRGB green  = CRGB::Green;

      return CRGBPalette16(red,  red,  red, red,
                           green, green, green, green,
                           red,  red,  red, red,
                           green, green, green, green );
    }

    CRGBPalette16 GetValentinesPalette()
    {
      CRGB red = CRGB::Red;
      CRGB white  = CRGB::Grey;

      return CRGBPalette16(white,  white,  white, white,
                           red, red, red, red,
                           white,  white,  white, white,
                           red, red, red, red );
    }

    CRGBPalette16 GetEasterPalette()
    {
      CRGB red = CRGB::Red;
      CRGB white  = CRGB::Grey;

      return CRGBPalette16(white,  white,  white, white,
                           red, red, red, red,
                           white,  white,  white, white,
                           red, red, red, red );
    }

    CRGBPalette16 GetPatrioticPalette()
    {
      CRGB blue = CRGB::Blue;
      CRGB white  = CRGB::Gray;
      CRGB red  = CRGB::Red;

      return CRGBPalette16(red,  white,  white, white,
                           white, white, blue, blue,
                           blue,  blue,  blue, red,
                           red, red, red, red );
    }


    // This example shows how to set up a static color palette
    // which is stored in PROGMEM (flash), which is almost always more
    // plentiful than RAM.  A static PROGMEM palette like this
    // takes up 64 bytes of flash.
    const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM =
    {
      CRGB::Red,
      CRGB::Gray, // 'white' is too bright compared to red and blue
      CRGB::Blue,
      CRGB::Black,

      CRGB::Red,
      CRGB::Gray,
      CRGB::Blue,
      CRGB::Black,

      CRGB::Red,
      CRGB::Red,
      CRGB::Gray,
      CRGB::Gray,

      CRGB::Blue,
      CRGB::Blue,
      CRGB::Black,
      CRGB::Black
    };

  public:

    void show(scenesTypeEnum showSceneType)
    {
      if (!currentPaletteHasBeenSet || currentScenesType != showSceneType)
      {
        changeCurrentPalette(showSceneType);
        currentPaletteHasBeenSet = true;
      }

      static uint8_t startIndex = 0;
      startIndex = startIndex + 1; /* motion speed */

      FillLEDsFromPaletteColors(startIndex);

      FastLED.show();
      FastLED.delay(1000 / UPDATES_PER_SECOND);
    }
};

LightsPattern_Scenes lightsPattern_Scenes;

#endif
