import numpy as np

def displayArrayDim(board):

    dispBoard = np.zeros(shape=np.shape(board))

    for i in range(np.shape(dispBoard)[0]):
        dispBoard[i][0] = i + 1

    for i in range(np.shape(dispBoard)[1]):
        dispBoard[0][i] = i + 1

    print(board)

def seedTheBoard(board):
    board[0][3] = 1
    board[1][3] = 1
    board[3][3] = 1
    board[4][3] = 1
    board[5][3] = 1
    board[7][3] = 1
    board[8][3] = 1

    print(board)

def main():
    numbOfRows = 9
    numbOfCols = 9

    board = np.zeros(shape=(numbOfRows,numbOfCols))

    displayArrayDim(board)

    seedTheBoard(board)

    

if __name__ == "__main__":
    main()