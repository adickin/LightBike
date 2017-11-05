#include "LightBike.h"


#include <FastLED.h>

//Should make a small class that does this for me.
namespace TestLedStrip
{
   const int DATA_PIN = 6;
   const int NUM_LEDS = 10;

   CRGB leds[NUM_LEDS];
}

namespace CircularWheelLedStrip
{
   const int DATA_PIN = 8;
   const int NUM_LEDS = 116;

   CRGB leds[NUM_LEDS];
}

const unsigned int CHANGE_INTERVAL_MS = 300;

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


   //FastLED.addLeds<NEOPIXEL, TestLedStrip::DATA_PIN>(TestLedStrip::leds, TestLedStrip::NUM_LEDS);

   FastLED.addLeds<NEOPIXEL, CircularWheelLedStrip::DATA_PIN>(CircularWheelLedStrip::leds, CircularWheelLedStrip::NUM_LEDS);


   for (int i = 0; i < CircularWheelLedStrip::NUM_LEDS; i++)
   {
      CircularWheelLedStrip::leds[i] = CRGB::Black;
   }


}

void LightBike::Loop()
{
   //unsigned int currentMilliseconds = millis();
   //if (!intervalReached(currentMilliseconds, g_previousMiliseconds, CHANGE_INTERVAL_MS))
   //{
   //   return;
   //}
   //g_previousMiliseconds = currentMilliseconds;


   for (int i = 0; i < CircularWheelLedStrip::NUM_LEDS; i++)
   {
      if (AreCRGBsEqual(CircularWheelLedStrip::leds[i], CRGB::White))
      {
         CircularWheelLedStrip::leds[i] = CRGB::Black;
      }
      else
      {
         CircularWheelLedStrip::leds[i] = CRGB::White;
      }
      

      //delay(100);
      FastLED.show();

   }

   //CRGB colorToUse = CRGB::White;

   //for (int i = 0; i < TestLedStrip::NUM_LEDS; i++)
   //{
   //   if (AreCRGBsEqual(g_leds[i], CRGB::White))
   //   {
   //      colorToUse = CRGB::Red;
   //   }

   //   g_leds[i] = colorToUse;
   //}

   //FastLED.show();
}

