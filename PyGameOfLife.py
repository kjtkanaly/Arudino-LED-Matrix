import numpy as np

# ----------------------------------------------------------------------------
def seedTheBoard(board):
    board[2][2] = 1
    board[2][3] = 1
    board[2][4] = 1
    board[2][5] = 1
    board[3][3] = 1
    board[3][4] = 1

    print(board)

# ----------------------------------------------------------------------------
def iterateGenerations(board, timeDelay):
    
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

# ----------------------------------------------------------------------------
def main():
    numbOfRows = 5
    numbOfCols = 5
    timeDelay = 1

    board = np.zeros(shape=(numbOfRows + 2, numbOfCols + 2))

    seedTheBoard(board)

    for i in range(1, 4):
        board = iterateGenerations(board, timeDelay)
        print(board)

    

if __name__ == "__main__":
    main()


