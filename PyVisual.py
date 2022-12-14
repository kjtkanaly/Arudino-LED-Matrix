import cv2
import numpy as np
from matplotlib import pyplot as plt

def main():
    img = cv2.imread("TestImage.png")

    imgData = np.asarray(img)

    downSampleRate = 10
    downImgData = np.zeros((round(imgData.shape[0] / downSampleRate),
                           round(imgData.shape[1] / downSampleRate),
                           3))

    print(f"OG Image Dim: {img.shape}")
    print(f"DS Image Dim: {downImgData.shape}")

    for row in range(0,img.shape[0],downSampleRate):
        for col in range(0,img.shape[1],downSampleRate):
            avgRedValue = np.mean(imgData[row:row + downSampleRate,
                                          col:col + downSampleRate, 0])
            avgGreenValue = np.mean(imgData[row:row + downSampleRate,
                                          col:col + downSampleRate, 1])
            avgBlueValue = np.mean(imgData[row:row + downSampleRate,
                                          col:col + downSampleRate, 2])
            
            imgRow = round(row / downSampleRate)
            imgCol = round(col / downSampleRate)
            downImgData[imgRow, imgCol, :] = [avgRedValue, 
                                              avgGreenValue, 
                                              avgBlueValue]

    # Plotting
    fig, (ax1, ax2) = plt.subplots(1, 2)
    ax1.imshow(imgData.astype(np.uint8))
    ax1.set_title("Original")
    ax2.imshow(downImgData.astype(np.uint8))
    ax2.set_title("Downsample")
    plt.show()
    
    
if __name__ == "__main__":
    main()