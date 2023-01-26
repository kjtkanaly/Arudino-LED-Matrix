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
int board[0][0];
int livingCellHue = 0;
int livingCellSat = 255;
int livingCellVal = 255;
int generationTimeDelay = 1000;
// Serial Parameters
int serialVal = 0;

CRGB leds[0];

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
  // Initilize the board
  board[numRows + 2][numCols + 2];
  
  // Assign initial cells
  board[4][5] = 1;
  board[5][5] = 1;
  board[6][6] = 1;
  board[7][7] = 1;

  // Display the board on the matrix
  displayBoardOnMatrix();
}

// ---------------------------------------------------------------------------
void iterateGenerations()
{

  int nextBoard[sizeof(board)[0]][sizeof(board)[1]];




  /*
  nextBoard = np.zeros(shape=np.shape(board))

    for row in range(1, np.shape(board)[0] - 1):
        for col in range(1, np.shape(board)[1] - 1):
            neighborCount = np.sum(board[row - 1:row + 2,
                                         col - 1:col + 2])
            neighborCount -= board[row][col]

            # Survive
            if (((neighborCount == 2) | (neighborCount == 3)) & 
                 (board[row][col] == 1)):
                nextBoard[row][col] = 1

            # Starve
            if ((neighborCount <= 1) & (board[row][col] == 1)):
                nextBoard[row][col] = 0

            # Overpopulate
            if ((neighborCount >= 4) & (board[row][col] == 1)):
                nextBoard[row][col] = 0

            # Create Life
            if ((neighborCount == 3) & (board[row][col] == 0)):
                nextBoard[row][col] = 1
    
    return nextBoard
    /**/
}

// ---------------------------------------------------------------------------
void displayBoardOnMatrix()
{
  for (int row = 1; row < numRows + 2; row++)
  {
    for (int col = 1; col < numCols + 2; col++)
    {
      if (board[row][col] == 1)
      {
        leds[row * numRows + col] = CHSV(livingCellHue, 
                                         livingCellSat, 
                                         livingCellVal);
      }
      else
      {
        leds[row * numRows + col] = CHSV(0, 0, 0);
      }
    }
  }

  FastLED.show();
}

// ---------------------------------------------------------------------------
void setup() 
{
  numLEDS = numRows * numCols;

  // Initialize the LED matrix
  leds[numLEDS];
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
      break;
  }
}
