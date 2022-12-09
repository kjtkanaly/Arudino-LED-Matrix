#include <FastLED.h>

# define numLEDS 25
# define LED_Pin 2

int rowTotal = 5;
int colTotal = 5;
int row;
int col;

CRGB leds[numLEDS];


void setup() 
{
  // Initialize the LED matrix
  FastLED.addLeds<WS2812B, LED_Pin, GRB>(leds,numLEDS);
  FastLED.setBrightness(brightness);

  // Turn the LEDs off
  for(int i = 0; i < numLEDS; i++)
  {
    leds[i] = CHSV(0, 0, 0);
  }
  FastLED.show();

  // Initialize my logic check LEDs
  pinMode(LED_BUILTIN, OUTPUT);
}


void loop()
{
  LED_crawlTest();
}


void LED_crawlTest(int crawlDelay = 100)
{
  for (int i = 0; i < numLEDS; i++)
  {
    leds[i] = CHSV(0, 250, 200);
    FastLED.show();

    delay(crawlDelay);

    leds[i] = CHSV(0, 0, 0);
    FastLED.show();
  }
}