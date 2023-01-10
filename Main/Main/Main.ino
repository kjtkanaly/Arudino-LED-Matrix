#include <FastLED.h>

# define numLEDS 25
# define LED_Pin 2

bool Mode = 0;

int ledBrightness = 25;
int rowTotal = 5;
int colTotal = 5;
int row;
int col;

CRGB leds[numLEDS];

// ---------------------------------------------------------------------------
void blink()
{
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);  
}

// ---------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------
void setup() 
{
  if (Mode == 0)
  {
    pinMode(LED_BUILTIN, OUTPUT);
  }

  else if (Mode == 1)
  {
    // Initialize the LED matrix
    FastLED.addLeds<WS2812B, LED_Pin, GRB>(leds,numLEDS);
    FastLED.setBrightness(ledBrightness);

    // Turn the LEDs off
    for(int i = 0; i < numLEDS; i++)
    {
      leds[i] = CHSV(0, 0, 0);
    }
    FastLED.show();

    // Initialize my logic check LEDs
    pinMode(LED_BUILTIN, OUTPUT);
  }
}

// ---------------------------------------------------------------------------
void loop()
{
  if (Mode == 0)
  {
    blink();
  }

  else if (Mode == 1)
  {
    LED_crawlTest();
  }
}
