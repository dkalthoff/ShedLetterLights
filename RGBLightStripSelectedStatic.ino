void StartSelectedStatic()
{
  for( int i = 0; i < NUM_LEDS; i++) 
  {
    leds[i].r = selectedStaticRed;
    leds[i].g = selectedStaticGreen;
    leds[i].b = selectedStaticBlue;
  }

  FastLED.show();
}
