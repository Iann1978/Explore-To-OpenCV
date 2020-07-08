# -*- coding: utf-8 -*-
"""
Created on Wed Jul  8 09:35:24 2020

@author: Iann
"""


import numpy as np
import cv2

o = np.zeros((128,128),dtype=np.uint8)
cv2.rectangle(o,(32,32),(96,96),255,-1)


k = np.zeros((25,25),dtype=np.uint8)
cv2.circle(k,(12,12),12,1,-1)
r= cv2.dilate(o,k)



cv2.imshow("origin",o)
cv2.imshow("erode result", r)
cv2.waitKey()
cv2.destroyAllWindows()