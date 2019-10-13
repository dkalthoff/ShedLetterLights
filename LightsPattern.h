#include <WiFi101.h>

enum lightsPatternEnum 
{
  originalLightsDemo,
  whitePulse,
  randomPulse,
  seasonalPattern,
  selectedPulse,
  selectedStatic,
  selectedSegments
};

enum seasons
{
  newYears_StartMonth,
  newYears_StartDay,
  newYears_EndMonth,
  newYears_EndDay,
  valentines_StartMonth,
  valentines_StartDay,
  valentines_EndMonth,
  valentines_EndDay,
  easter_StartMonth,
  easter_StartDay,
  easter_EndMonth,
  easter_EndDay,
  fourthOfJuly_StartMonth,
  fourthOfJuly_StartDay,
  fourthOfJuly_EndMonth,
  fourthOfJuly_EndDay
};

void setLightsPattern(lightsPatternEnum lightsPattern);
void defaultPageResponse(WiFiClient client);
