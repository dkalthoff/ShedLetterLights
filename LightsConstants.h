#ifndef LightsConstants_h
#define LightsConstants_h

#include <FastLED.h>

#define DEBUG 0
#if DEBUG == 1
#define debug(x) Serial.print(x)
#define debugln(x) Serial.println(x)
#else
#define debug(x)
#define debugln(x)
#endif

#define DATA_PIN     5
#define NUM_LEDS    135
#define BRIGHTNESS  64
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];

#define UPDATES_PER_SECOND 60

const byte RED = 0;
const byte GREEN = 1;
const byte BLUE = 2;

const byte numberLEDsSegment1Start = 0;
const byte numberLEDsSegment1End = 56;
const byte numberLEDsSegment2Start = 55;
const byte numberLEDsSegment2End = 94;
const byte numberLEDsSegment3Start = 95;
const byte numberLEDsSegment3End = 135;

typedef enum { scenes, whitePulse, randomPulse, randomStatic, selectedPulse,
               selectedStatic, selectedStaticSegments, randomStaticSegments
             } lightsPatternEnum;

const static struct {
  lightsPatternEnum val;
  const char *str;
} lightsPatternConversion [] = {
  {scenes, "Senes"},
  {whitePulse, "White Pulse"},
  {randomPulse, "Random Pulse"},
  {randomStatic, "Random Static"},
  {selectedPulse, "Selected Pulse"},
  {selectedStatic, "Selected Static"},
  {selectedStaticSegments, "Selected Static Segments"},
  {randomStaticSegments, "Random Static Segments"}
};

lightsPatternEnum getLightsPattern (const char *str)
{
  int j;
  for (j = 0;  j < sizeof (lightsPatternConversion) / sizeof (lightsPatternConversion[0]);  ++j)
    if (strcmp (str, lightsPatternConversion[j].str))
      return lightsPatternConversion[j].val;
}

char getLightsPattern (lightsPatternEnum lightsPattern)
{
  int j;
  for (j = 0;  j < sizeof (lightsPatternConversion) / sizeof (lightsPatternConversion[0]);  ++j)
    if (lightsPattern == lightsPatternConversion[j].val)
      return *lightsPatternConversion[j].str;
}

typedef enum { avonlakers, christmas, easter, forest, heat, lava, 
              ocean, party, patriotic, purplepride, rainbow, randomDraw, valentines } scenesTypeEnum;

const static struct {
  scenesTypeEnum val;
  const char *str;
} scenesTypeConversion [] = {
  {avonlakers, "Avon Lakers"},
  {christmas, "Christmas"},
  {easter, "Easter"},
  {forest, "Forest"},
  {heat, "Heat"},
  {lava, "Lava"},
  {ocean, "Ocean"},
  {party, "Party"},
  {patriotic, "Patriotic"},
  {purplepride, "Purple Pride"},
  {rainbow, "Rainbow"},
  {randomDraw, "Random"},
  {valentines, "Valentines"}
};

scenesTypeEnum getScenesType (const char *str)
{
  int j;
  for (j = 0;  j < sizeof (scenesTypeConversion) / sizeof (scenesTypeConversion[0]);  ++j)
    if (strcmp (str, scenesTypeConversion[j].str))
      return scenesTypeConversion[j].val;
}

char getScenesType (scenesTypeEnum scenesType)
{
  int j;
  for (j = 0;  j < sizeof (scenesTypeConversion) / sizeof (scenesTypeConversion[0]);  ++j)
    if (scenesType == scenesTypeConversion[j].val)
      return *scenesTypeConversion[j].str;
}

typedef struct {
  bool isValid;
  lightsPatternEnum lightsPattern;
  scenesTypeEnum scenesType;
  const char *info;
} LightsConfiguration;

#endif
