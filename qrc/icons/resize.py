import cv2 

img=cv2.imread('./Calibration_4.png')
resized=cv2.resize(img,(230,187))
cv2.imwrite('calibration.png',resized)
