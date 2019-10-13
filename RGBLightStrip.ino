#include <FastLED.h>

#define LED_PIN     5
#define NUM_LEDS    135
#define BRIGHTNESS  64
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];

#define UPDATES_PER_SECOND 100

CRGBPalette16 currentPalette;
TBlendType    currentBlending;

extern CRGBPalette16 myRedWhiteBluePalette;
extern const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM;

bool lightsAreCleared = false;

void configureRGBLightStrip()
{
  randomSeed(analogRead(0)); // seed the random generator
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(  BRIGHTNESS );
  
  currentPalette = RainbowColors_p;
  currentBlending = LINEARBLEND;
  Serial.println("RGB Light Strip Configured");
}

void setLightsPattern(lightsPatternEnum lightsPattern)
{
    if(lightAreOn && (shouldOverrideSunset || isAfterSunset()))
    {
      lightsAreCleared = false;
      
      switch (lightsPattern) 
      {
        case originalLightsDemo:
          OriginalLightsDemo();
          break;
        case whitePulse:
          StartWhitePulse();
          break;
        case randomPulse:
          StartRandomPulse();
          break;
        case selectedPulse:
          StartSelectedPulse();
          break;
        case selectedStatic:
          StartSelectedStatic();
          break;
        case selectedSegments:
          StartSelectedSegments();
          break;
        case seasonalPattern:
          setLightsPattern(getSeasonalPattern());
          break;
      }
    }
    else
    {
      if(!lightsAreCleared)
      {
        FastLED.clear();
        FastLED.show();
        lightsAreCleared = true;
      }
    }
}

lightsPatternEnum getSeasonalPattern()
{
  return whitePulse;
}

String getCurrentLightPatternAsString(lightsPatternEnum lightsPattern)
{
  String pattern = "";
  
  switch (lightsPattern) 
  {
    case originalLightsDemo:
      pattern = "originalLightsDemo";
      break;
    case whitePulse:
      pattern = "whitePulse";
      break;
    case randomPulse:
      pattern = "randomPulse";
      break;
    case seasonalPattern:
      getCurrentLightPatternAsString(getSeasonalPattern());
      break;
    case selectedPulse:
      pattern = "selectedPulse";
      break;
    case selectedStatic:
      pattern = "selectedStatic";
      break;
    case selectedSegments:
      pattern = "selectedSegments";
      break;
    default:
      pattern = "Unsupported pattern.";
      break;
  }

  return pattern;
}

void printCurrentLightPattern(lightsPatternEnum lightsPattern)
{
  Serial.println("Current lights pattern: " + getCurrentLightPatternAsString(lightsPattern));
}
