#ifndef LightsPattern_SelectedStatic_h
#define LightsPattern_SelectedStatic_h

#include <FastLED.h>

class LightsPattern_SelectedStatic
{
  private:
  
    char currentSelectedColor[7];
    
  public:

    void show(const char *selectedColor)
    {
      if (strcmp(currentSelectedColor, selectedColor) != 0)
      {
        char colorHex[9] = "0x";
        strcat(colorHex, selectedColor);
        long colorAsLong = strtol(colorHex, NULL, 0);
        
        for ( int i = 0; i < NUM_LEDS; i++) 
        {
          leds[i] = colorAsLong;
        }
        FastLED.show();
        debugln(selectedColor);
        debug("Static color change from ");
        debug(currentSelectedColor);
        
        strcpy(currentSelectedColor, selectedColor);
        
        debug(" to ");
        debugln(currentSelectedColor);
      }
    }
};

LightsPattern_SelectedStatic lightsPattern_SelectedStatic;

#endif
