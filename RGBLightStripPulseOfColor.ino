void StartWhitePulse()
{
  PulseInOut(0xff, 0xff, 0xff);
}

void StartRandomPulse()
{
  PulseInOut(random8(), random8(), random8());
}

void StartSelectedPulse()
{
  PulseInOut(selectedPulseRed, selectedPulseGreen, selectedPulseBlue);
}

void PulseInOut(byte red, byte green, byte blue)
{
  float r, g, b;
      
  for(int k = 0; k < 256; k=k+1) 
  { 
    r = (k/256.0)*red;
    g = (k/256.0)*green;
    b = (k/256.0)*blue;
    setAll(r,g,b);
    delay(10);
  }
     
  for(int k = 255; k >= 0; k=k-2) 
  {
    r = (k/256.0)*red;
    g = (k/256.0)*green;
    b = (k/256.0)*blue;
    setAll(r,g,b);
    delay(10);
  }
}

void setAll(byte red, byte green, byte blue) 
{
  for(int i = 0; i < NUM_LEDS; i++ ) 
  {
    setPixel(i, red, green, blue); 
  }

  FastLED.show();
}

void setPixel(int Pixel, byte red, byte green, byte blue) 
{
   leds[Pixel].r = red;
   leds[Pixel].g = green;
   leds[Pixel].b = blue;
}
