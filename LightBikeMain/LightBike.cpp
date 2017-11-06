#include "LightBike.h"


#include <FastLED.h>

namespace CircularWheelLedStrip
{
   const int DATA_PIN = 8;
   const int NUM_LEDS = 116;

   CRGB leds[NUM_LEDS];
}

namespace SpokesWheelStrip
{
   const int DATA_PIN = 7;
   const int LEDS_PER_SPOKE = 16;
   const int NUMBER_OF_SPOKES = 6;

   const int NUM_LEDS = LEDS_PER_SPOKE * NUMBER_OF_SPOKES;

   CRGB leds[NUM_LEDS];
}

const unsigned int CHANGE_INTERVAL_MS = 25;

unsigned int g_previousMiliseconds;


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

   FastLED.addLeds<NEOPIXEL, CircularWheelLedStrip::DATA_PIN>(CircularWheelLedStrip::leds, CircularWheelLedStrip::NUM_LEDS);
   FastLED.addLeds<NEOPIXEL, SpokesWheelStrip::DATA_PIN>(SpokesWheelStrip::leds, SpokesWheelStrip::NUM_LEDS);



   for (int i = 0; i < CircularWheelLedStrip::NUM_LEDS; i++)
   {
      CircularWheelLedStrip::leds[i] = CRGB::Black;
   }

   for (int i = 0; i < SpokesWheelStrip::NUM_LEDS; i++)
   {
      SpokesWheelStrip::leds[i] = CRGB::Black;
   }


}



int g_currentWheelLedIndex = 0;

int GetPreviousWheelLedIndex()
{
   int previousLedIndex = 0;

   if (g_currentWheelLedIndex == 0)
   {
      previousLedIndex = CircularWheelLedStrip::NUM_LEDS - 1;
   }
   else
   {
      previousLedIndex = g_currentWheelLedIndex - 1;
   }
   return previousLedIndex;
}

int GetNextWheelLedIndex()
{
   int nextLedIndex = 0;

   if (g_currentWheelLedIndex + 1 != CircularWheelLedStrip::NUM_LEDS)
   {
      nextLedIndex = g_currentWheelLedIndex + 1;
   }

   return nextLedIndex;
}

int GetSpokeIndex(int currentWheelLedIndex)
{
   int spokeIndex = -1;

   if (currentWheelLedIndex == 0 ||
      currentWheelLedIndex == 1 ||
      currentWheelLedIndex == CircularWheelLedStrip::NUM_LEDS - 1)
   {
      spokeIndex = 0;
   }
   else if (
      currentWheelLedIndex == 18 ||
      currentWheelLedIndex == 19 ||
      currentWheelLedIndex == 20 )
   {
      spokeIndex = 1;
   }
   else if (
      currentWheelLedIndex == 37 ||
      currentWheelLedIndex == 38 ||
      currentWheelLedIndex == 39)
   {
      spokeIndex = 2;
   }
   else if (
      currentWheelLedIndex == 57 ||
      currentWheelLedIndex == 58 ||
      currentWheelLedIndex == 59)
   {
      spokeIndex = 3;
   }
   else if (
      currentWheelLedIndex == 74 ||
      currentWheelLedIndex == 75 ||
      currentWheelLedIndex == 76)
   {
      spokeIndex = 4;
   }
   else if (
      currentWheelLedIndex == 95 ||
      currentWheelLedIndex == 96 ||
      currentWheelLedIndex == 97)
   {
      spokeIndex = 5;
   }
   return spokeIndex;
}

void LightBike::Loop()
{
   unsigned int currentMilliseconds = millis();
   if (!intervalReached(currentMilliseconds, g_previousMiliseconds, CHANGE_INTERVAL_MS))
   {
      return;
   }
   g_previousMiliseconds = currentMilliseconds;

   //turn off previous Leds;
   int previousWheelLedIndex = GetPreviousWheelLedIndex();
   int nextWheelLedIndex = GetNextWheelLedIndex();
   CircularWheelLedStrip::leds[previousWheelLedIndex] = CRGB::Black;
   CircularWheelLedStrip::leds[g_currentWheelLedIndex] = CRGB::Black;
   CircularWheelLedStrip::leds[nextWheelLedIndex] = CRGB::Black;

   g_currentWheelLedIndex = GetNextWheelLedIndex();
   previousWheelLedIndex = GetPreviousWheelLedIndex();
   nextWheelLedIndex = GetNextWheelLedIndex();
   CircularWheelLedStrip::leds[previousWheelLedIndex] = CRGB::DodgerBlue;
   CircularWheelLedStrip::leds[g_currentWheelLedIndex] = CRGB::DodgerBlue;
   CircularWheelLedStrip::leds[nextWheelLedIndex] = CRGB::DodgerBlue;


   int spokeIndex = GetSpokeIndex(g_currentWheelLedIndex);
   if (spokeIndex != -1)
   {
      for (int i = spokeIndex * 16; i < (spokeIndex * 16) + 16; i++) 
      {
         SpokesWheelStrip::leds[i] = CRGB::DeepSkyBlue;
      }
   }
   else {
      for (int i = 0; i < SpokesWheelStrip::NUM_LEDS; i++) {
         SpokesWheelStrip::leds[i] = CRGB::Black;
      }
   }

   FastLED.show();
}

