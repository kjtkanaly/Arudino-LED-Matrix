from bitstring import BitArray

import numpy as np
import struct
import serial

# ----------------------------------------------------------------------------
def seedTheBoard(board):
    board[2][2] = 1
    board[2][3] = 1
    board[2][4] = 1
    board[2][5] = 1
    board[3][3] = 1
    board[3][4] = 1

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
def convertIntToByte(val, base):
    byte = struct.pack(base, val)
    return byte

# ----------------------------------------------------------------------------
def convertByteToBinary(hex, base):
    binary = bin(int(hex, base))
    return binary

# ----------------------------------------------------------------------------
def testByteFxs():
    for i in range(0, 128):
        byte = convertIntToByte(i, "b")
        binary = convertByteToBinary(hex=byte.hex(), base=16)

        print(str(i).zfill(3) + ": " + 
              str(byte.hex()) + ", " + 
              binary[2:].zfill(7))

# ----------------------------------------------------------------------------
def transmitNewBoard(board):
     for row in range(1, np.shape(board)[0] - 1):
        for col in range(1, np.shape(board)[1] - 1):
            byte = convertIntToByte(val=int(board[row, col]), base="b")
            binary = convertByteToBinary(hex=byte.hex(), base=16)

            print(str(board[row,col]) + ": " + str(byte))

# ----------------------------------------------------------------------------
def main():
    numbOfRows = 5
    numbOfCols = 5
    timeDelay = 1
    gameLoopCount = 0

    board = np.zeros(shape=(numbOfRows + 2, numbOfCols + 2))

    seedTheBoard(board)
    print(board)

    transmitNewBoard(board)

    for i in range(1, gameLoopCount + 1):
        board = iterateGenerations(board, timeDelay)
        print(board)

        transmitNewBoard(board)
        

# ----------------------------------------------------------------------------
if __name__ == "__main__":
    main()


