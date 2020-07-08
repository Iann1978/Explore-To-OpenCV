# -*- coding: utf-8 -*-
"""
Created on Wed Jul  8 09:25:30 2020

@author: Iann
"""


import cv2
import numpy as np

o = cv2.imread("../images/dilation.png")
k = np.ones((5,5))
r = cv2.erode(o,k)

cv2.imshow("origin", o)
cv2.imshow("erode result", r)
cv2.waitKey()
cv2.destroyAllWindows()