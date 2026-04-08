import numpy as np 
import cv2

def get_limit(color):
    c = np.uint8([[color]])
    hsvColor = cv2.cvtColor(c , cv2.COLOR_BGR2HSV)
    
    low_lim = hsvColor[0][0][0] - 10, 100, 100
    high_lim = hsvColor[0][0][0] + 10, 255, 255
    
    low_lim = np.array(low_lim,dtype=np.uint8)
    high_lim = np.array(high_lim,dtype=np.uint8)
    
    return low_lim, high_lim