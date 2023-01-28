#include <FastLED.h>

# define LED_Pin 3

enum MatrixMode
{
  fillBoardRB = 0,
  ledCrawl = 1,
  gameOfLife = 2
};

// LED Matrix Parameters
int matrixMode = MatrixMode::gameOfLife;
int ledBrightness = 25;
int saturation = 255;
int value = 255;
int numRows = 9;
int numCols = 9;
int numLEDS;
// GameOfLife Parameters
int board[11][11];
int livingCellHue = 0;
int livingCellSat = 255;
int livingCellVal = 255;
int generationTimeDelay = 1000;
// Serial Parameters
int serialVal = 0;

CRGB leds[81];

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
    leds[i] = CHSV(0, saturation, value);
    FastLED.show();

    delay(crawlDelay);

    leds[i] = CHSV(0, 0, 0);
    FastLED.show();
  }
}

// ---------------------------------------------------------------------------
void LED_FillTest()
{
  fill_solid(leds, numLEDS, CHSV(0, saturation, value));
  FastLED.show();
}

// ---------------------------------------------------------------------------
void turnOffAllLEDS()
{
  // Turn the LEDs off
  for(int i = 0; i < numLEDS; i++)
  {
    leds[i] = CHSV(0, 0, 0);
  }
  FastLED.show();
}

// ---------------------------------------------------------------------------
void seedGameBoard()
{
  // Set Next Board to zero initially
  for (int row = 0; row < numRows + 2; row++)
  {
    for (int col = 0; col < numCols + 2; col++)
    {
      board[row][col] = 0;
    }
  }

  board[1][1] = 1;
  //board[9][1] = 1;
  //board[1][9] = 1;

  // Assign initial cells
  board[2][5] = 1;
  board[3][5] = 1;
  board[4][5] = 1;
  board[5][5] = 1;
  board[6][5] = 1;
  board[6][6] = 1;
  board[7][7] = 1;

  // Display the board on the matrix
  displayBoardOnMatrix();

  delay(generationTimeDelay);
}

// ---------------------------------------------------------------------------
void iterateGenerations()
{
  int nextBoard[sizeof(board) / sizeof(board[0])][sizeof(board[0]) / sizeof(board[0][0])];

  // Set Next Board to zero initially
  for (int row = 0; row < numRows + 2; row++)
  {
    for (int col = 0; col < numCols + 2; col++)
    {
      nextBoard[row][col] = 0;
    }
  }

  /*
  Serial.print(sizeof(nextBoard) / sizeof(nextBoard[0]));
  Serial.print(",");
  Serial.print(sizeof(nextBoard[0]) / sizeof(nextBoard[0][0]));
  Serial.print("\n");
  /**/

  for (int row = 1; row <= numRows; row++)
  {
    for (int col = 1; col <= numCols; col++)
    {
      int neighborCount = 0;

      // Sum the neighbors
      for (int y = row - 1; y <= (row + 1); y++)
      {
        for (int x = col - 1; x <= (col + 1); x++)
        {
          neighborCount += board[y][x];
        }
      }

      neighborCount -= board[row][col];

      //Serial.print(String(neighborCount) + ": " + String(row) + "x" + String(col) + "\n");

      // Survive
      if (((neighborCount == 2) || (neighborCount == 3)) && (board[row][col] == 1))
      {
        nextBoard[row][col] = 1;
      }

      // Starve
      if ((neighborCount <= 1) && (board[row][col] == 1))
      {
        nextBoard[row][col] = 0;
      }

      // Overpopulate
      if ((neighborCount >= 4) && (board[row][col] == 1))
      {
        nextBoard[row][col] = 0;
      }

      //Create Life
      if ((neighborCount == 3) && (board[row][col] == 0))
      {
        nextBoard[row][col] = 1;
      }

      // Serial.print(String(neighborCount) + ": " + String(row) + "x" + String(col) + "=" + String(nextBoard[row][col]) + "\n");
    }
  }
  
  for (int row = 0; row < (numRows + 2); row++)
  {
    for (int col = 0; col < (numCols + 2); col++)
    {
      board[row][col] = nextBoard[row][col];
    }
  }

  displayBoardOnMatrix();

  delay(generationTimeDelay);
}

// ---------------------------------------------------------------------------
void displayBoardOnMatrix()
{
  for (int row = 1; row <= numRows; row++)
  {
    for (int col = 1; col <= numCols; col++)
    {
      int index = (col - 1) * numCols + (row - 1);

      //Serial.print(index);
      //Serial.print(": " + String(row) + "x" + String(col) + "\n");

      if (board[row][col] == 1)
      {
        leds[index] = CHSV(livingCellHue, 
                           livingCellSat, 
                           livingCellVal);
      }
      else
      {
        leds[index] = CHSV(0, 0, 0);
      }
    }
  }

  FastLED.show();
}

// ---------------------------------------------------------------------------
void setup() 
{
  Serial.begin(9600);

  // Initialize the LED matrix
  numLEDS = numRows * numCols;
  FastLED.addLeds<WS2812B, LED_Pin, GRB>(leds,numLEDS);
  FastLED.setBrightness(ledBrightness);

  turnOffAllLEDS();

  if (matrixMode == MatrixMode::gameOfLife)
  {
    seedGameBoard();
  }
}

// ---------------------------------------------------------------------------
void loop()
{  
  /*
  Serial.print(sizeof(board) / sizeof(board[0]));
  Serial.print(",");
  Serial.print(sizeof(board[0]) / sizeof(board[0][0]));
  Serial.print("\n");
  delay(1000);
  /**/

  switch (matrixMode)
  {
    case (MatrixMode::fillBoardRB):
      LED_FillTest();
      break;
    case (MatrixMode::ledCrawl):
      LED_crawlTest();
      break;
    case (MatrixMode::gameOfLife):
      iterateGenerations();
      // matrixMode = 3;
      break;
  }/**/
}
