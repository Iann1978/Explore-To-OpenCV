# -*- coding: utf-8 -*-
"""
Created on Mon Jul 13 09:01:55 2020

@author: Iann
"""


import cv2
import numpy as np

o = cv2.imread('../images/sharr.jpg',cv2.IMREAD_GRAYSCALE)
print(o.shape)  
print(o.dtype)
r,o1 =cv2.threshold(o,128,255,cv2.THRESH_BINARY)
gx = cv2.Scharr(o1,cv2.CV_64F,1,0)
gx = cv2.convertScaleAbs(gx)

gy = cv2.Scharr(o1,cv2.CV_64F,0,1)
gy = cv2.convertScaleAbs(gy)

gxy = cv2.addWeighted(gx,1,gy,1,0)
print('gx.dtype:', gx.dtype)


cv2.imshow("origin",o)
cv2.imshow('origin1',o1)
cv2.imshow('scharr_gx', gx)
cv2.imshow('scharr_gy', gy) 
cv2.imshow('gxy', gxy)



cv2.waitKey()
cv2.destroyAllWindows();