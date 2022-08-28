import cv2 as cv
import numpy as np
from matplotlib import pyplot as plt
import serial
import time

Arduino = serial.Serial('com5',9600)
time.sleep(2)

cam =cv.VideoCapture(0)
lower = np.array([0,125,125])
upper = np.array([10,255,255])
while(1):
     ret,frame =cam.read()
     frame = cv.flip(frame,1)
     w=frame.shape[1]
     h=frame.shape[0]

     img_smooth = cv.GaussianBlur(frame,(7,7),0)

     #definr region of intersser
     mask =np.zeros_like(frame)
     mask[50:350,50:350] = [255,255,255]
     img_roi = cv.bitwise_and(img_smooth,mask)
     cv.rectangle(frame,(50,50),(350,350),(0,0,255),2)
     cv.line(frame,(150,50),(150,350),(0,0,255),1)
     cv.line(frame,(250,50),(250,350),(0,0,255),1)
     cv.line(frame,(50,150),(350,150),(0,0,255),1)
     cv.line(frame,(50,250),(350,250),(0,0,255),1)
     
     img_hsv = cv.cvtColor(img_smooth,cv.COLOR_BGR2HSV)
     img_threshold = cv.inRange(img_hsv,lower,upper)

     contours,hirarchy = cv.findContours(img_threshold,cv.RETR_TREE,cv.CHAIN_APPROX_NONE)

     if(len(contours)!=0):
         areas =[cv.contourArea(c) for c in contours]
         max_index = np.argmax(areas)
         cnt = contours[max_index]

         M=cv.moments(cnt)
         
         if(M['m00']!=0):
              cx = int(M['m10']/M['m00'])
              cy = int(M['m01']/M['m00'])
              cv.circle(frame,(cx,cy),4,(0,255,0),-1)

              if cx in range(150,250):
                   
                   if cy<150:
                       Arduino.write(b'f')
                       print("forward")
                   elif cy>250:
                       Arduino.write(b'b')
                       print("backward")
                   else:
                       Arduino.write(b's')
                       print("stop")
              if cy in range(150,250):
                   if cx<150 :
                       Arduino.write(b'l')
                       print("left")
                   elif cx>250:
                       Arduino.write(b'r')
                       print("right")
                   else:
                       Arduino.write(b's')
                       print("stop")
                        
                   
          
     
         
     cv.imshow("Frame",frame)
     key=cv.waitKey(10)
     
     if key == 27:
         break
cam.release()
cv.destroyAllWindows()
