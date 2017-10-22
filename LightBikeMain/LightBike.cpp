#include "LightBike.h"


#include <FastLED.h>

#define DATA_PIN 6
#define NUM_LEDS 60
const unsigned int CHANGE_INTERVAL_MS = 300;

unsigned int g_previousMiliseconds;
CRGB g_leds[NUM_LEDS];


bool AreCRGBsEqual(
   const CRGB& currentColor,
   const CRGB& compareColor)
{
   return (currentColor.red == compareColor.red) &&
      (currentColor.green == compareColor.green) &&
      (currentColor.blue == compareColor.blue);
}

bool intervalReached(unsigned int currentTimeMs, unsigned int previousTimeMs, unsigned int intervalMs)
{
   return (currentTimeMs - previousTimeMs) >= intervalMs;
}

void LightBike::Setup()
{
   g_previousMiliseconds = 0u;


   FastLED.addLeds<NEOPIXEL, DATA_PIN>(g_leds, NUM_LEDS);
}

void LightBike::Loop()
{
   unsigned int currentMilliseconds = millis();
   if (!intervalReached(currentMilliseconds, g_previousMiliseconds, CHANGE_INTERVAL_MS))
   {
      return;
   }
   g_previousMiliseconds = currentMilliseconds;

   CRGB colorToUse = CRGB::White;

   for (int i = 0; i < 10; i++)
   {
      if (AreCRGBsEqual(g_leds[i], CRGB::White))
      {
         colorToUse = CRGB::Red;
      }

      g_leds[i] = colorToUse;
   }

   FastLED.show();
}

