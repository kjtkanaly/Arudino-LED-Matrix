#include <FastLED.h>

# define numLEDS 25
# define LED_Pin 2

bool Mode = 0;

const int bufferSize = 50;
int ledBrightness = 25;
int rowTotal = 5;
int colTotal = 5;
int row;
int col;
int serialData;

byte serialBuffer[bufferSize];

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
void readInGameBoardValue()
{  
  if (Serial.available())
  {
    digitalWrite(LED_BUILTIN, HIGH);

    int numbOfBytes = Serial.readBytes(serialBuffer, bufferSize);

    for (int i = 0; i < numbOfBytes; i++)
    {
      Serial.print(serialBuffer[i]);
    }
  }
  // digitalWrite(LED_BUILTIN, LOW);
}

// ---------------------------------------------------------------------------
void setup() 
{
  if (Mode == 0)
  {
    pinMode(LED_BUILTIN, OUTPUT);

    // Begin the serial comms
    Serial.begin(9600);
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
    // blink();
    readInGameBoardValue();
  }

  else if (Mode == 1)
  {
    LED_crawlTest();
  }
}
