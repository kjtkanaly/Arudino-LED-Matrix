from serial.tools.list_ports import comports

import numpy as np
import struct
import serial
import time

# ----------------------------------------------------------------------------
def initiateBoard(numbOfRows, numbOfCols, seedBoard):
    board = np.zeros(shape=(numbOfRows + 2, numbOfCols + 2))

    if seedBoard:
        board = seedTheBoard(board)

    return board

# ----------------------------------------------------------------------------
def seedTheBoard(board):
    board[2][2] = 1
    board[2][3] = 1
    board[2][4] = 1
    board[2][5] = 1
    board[3][3] = 1
    board[3][4] = 1

    return board

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
def transmitNewBoard(board, serialPort):
     for row in range(1, np.shape(board)[0] - 1):
        for col in range(1, np.shape(board)[1] - 1):
            byte = convertIntToByte(val=int(board[row, col]), base="i")
            binary = convertByteToBinary(hex=byte.hex(), base=16)

            print(str(board[row,col]) + ": " + str(byte))

            numbOfBytesSent = serialPort.write(byte)
            print(numbOfBytesSent)

# ----------------------------------------------------------------------------
def testByteTransmitToArduino(arduino):
    byte = convertIntToByte(1,"b")
    print(byte)
    sentBytes = arduino.write(byte)
    print("Number of Transmitted Bytes: " + str(sentBytes))

    time.sleep(1)

    print(str(arduino.in_waiting))
    rxBytes = arduino.read(size=16)
    print(rxBytes)

# ----------------------------------------------------------------------------
def rxByteFromArduino(arduino, byteSize):
    rxByte = serial.Serial.read(size=byteSize)
    print(rxByte)

# ----------------------------------------------------------------------------
def listSerialPorts():

    if len(comports()) == 0:
        print("No comports to list!")
        return

    for port in comports():
        print(port.device + ", " + port.description)

# ----------------------------------------------------------------------------
def getUSBPortObject():
    portObject = None
    for port in comports():
        if port.description != "n/a":
            portObject = port
            break  
    return portObject
        
# ----------------------------------------------------------------------------
def getSerialObject(serialPort, timeout):   
    if serialPort != None:
        print(serialPort.device)
        arduino = serial.Serial(port=serialPort.device, timeout=timeout)
        return arduino
    else:
        print("Whops! No serial port XD")
        return None

# ----------------------------------------------------------------------------
def main():
    # Board/Game Parameters
    numbOfRows = 5
    numbOfCols = 5
    timeDelay = 1
    gameLoopCount = 0

    board = initiateBoard(numbOfRows, numbOfCols, True)
    print(board)

    # Serial Parameters
    timeout = 1
    byteSizes = 8

    listSerialPorts()
    arduinoPort = getUSBPortObject()
    arduino = getSerialObject(serialPort=arduinoPort, timeout=timeout)

    if arduino != None:
        rxByteFromArduino(arduino=arduino, byteSize=byteSizes)

        for i in range(1, gameLoopCount + 1):
            board = iterateGenerations(board, timeDelay)
            print(board)

            transmitNewBoard(board=board, serialPort=arduino)
            
        arduino.close()

# ----------------------------------------------------------------------------
if __name__ == "__main__":
    main()


