const byte numberLEDsSegment1Start = 0;
const byte numberLEDsSegment1End = 56;
const byte numberLEDsSegment2Start = 55;
const byte numberLEDsSegment2End = 94;
const byte numberLEDsSegment3Start = 95;
const byte numberLEDsSegment3End = 135;

void StartSelectedSegments()
{
  // Segment 1
  for(byte i = numberLEDsSegment1Start; i < numberLEDsSegment1End; i++)
  {
    leds[i].r = selectedSegmentsRed1;
    leds[i].g = selectedSegmentsGreen1;
    leds[i].b = selectedSegmentsBlue1;
  }
  
  // Segment 2
  for(byte i = numberLEDsSegment2Start; i < numberLEDsSegment2End; i++)
  {
    leds[i].r = selectedSegmentsRed2;
    leds[i].g = selectedSegmentsGreen2;
    leds[i].b = selectedSegmentsBlue2;
  }
  
  // Segment 3
  for(byte i = numberLEDsSegment3Start; i < numberLEDsSegment3End; i++)
  {
    leds[i].r = selectedSegmentsRed3;
    leds[i].g = selectedSegmentsGreen3;
    leds[i].b = selectedSegmentsBlue3;
  }

  FastLED.show();
}
