import cv2
import numpy as np
from matplotlib import image

def main():
    img = cv2.imread("TestImage.png")

    cv2.imshow("Test Image",img)
    cv2.waitKey( )
    cv2.destroyAllWindows

    imgData = np.asarray(img)

    downSampleRate = 4
    downImgData = np.zeros((round(imgData.shape[0] / downSampleRate),
                           round(imgData.shape[1] / downSampleRate),
                           3))

    print(f"OG Image Dim: {img.shape}")
    print(f"DS Image Dim: {downImgData.shape}")

    for row in range(0,img.shape[0],downSampleRate):
        for col in range(0,img.shape[1],downSampleRate):
            avgRedValue = np.mean(imgData[row:row + downSampleRate,
                                          col:col + downSampleRate, 1])
            avgBlueValue = np.mean(imgData[row:row + downSampleRate,
                                          col:col + downSampleRate, 1])
            avgGreenValue = np.mean(imgData[row:row + downSampleRate,
                                          col:col + downSampleRate, 1])
            
            imgRow = row / downSampleRate
            imgCol = col / downSampleRate
            downImgData[imgRow, imgCol, :] = [avgRedValue, 
                                              avgBlueValue, 
                                              avgGreenValue]
            


    

if __name__ == "__main__":
    main()