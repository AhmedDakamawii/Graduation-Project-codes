
import importlib.util

# Check if the ultralytics module is available
if importlib.util.find_spec("ultralytics") is not None:
    from ultralytics import YOLO
else:
    print("Ultralytics module is not installed. Please make sure to install it using 'pip install ultralytics'.")

import cv2
import numpy as np
import urllib.request
import serial
import pathlib 
temp = pathlib.PosixPath 
pathlib.PosixPath = pathlib.WindowsPath
url = 'http://172.20.10.6/capture?'

arduino_port = 'COM4'  # Modify this with the appropriate serial port
baud_rate = 9600  # Modify this with the appropriate baud rate

cap = cv2.VideoCapture(url)
#cap = cv2.VideoCapture(0)

model = YOLO(model='C:/Users/a7med/Desktop/Sign Recog Final/best3.pt') #Load model+
classes = model.names #Class names


 #Establish serial connection with Arduino Nano
arduino = serial.Serial(arduino_port, baud_rate, timeout=1)

def send_servo_command(angle):
    command = f"{angle}\n"  # Append newline character to the command
    arduino.write(command.encode('utf-8'))


def findObject(img):
    
    results = model(img)
    boxes = results[0].boxes #Bounding boxes around the detected objects in the single frame with properties like label, confidence ratio, etc.. 
    frame = results[0].plot()

    for box in boxes:
        
        #edit this part with the new classes names
        
        if classes[int(box.cls[0].tolist())] == 'stop':
            print("STOP")
            send_servo_command(1)  
        elif classes[int(box.cls[0].tolist())] == 'speed_limit_60':
            print("Speed Limit 60")
            send_servo_command(2)
        # elif classes[int(box.cls[0].tolist())] == 'Pedestrian_Crossing':
        #     print("Pedestrian Crossing")
        #     send_servo_command(2)    
        # elif classes[int(box.cls[0].tolist())] == 'Warning':
        #     print("Warning")
        #     send_servo_command(2)          
        elif classes[int(box.cls[0].tolist())] == 'speed_limit_80':
            print("Speed Limit 80")
            send_servo_command(3)
        elif classes[int(box.cls[0].tolist())] == 'do_not_enter':
            print("Don't enter")
            send_servo_command(8)
        elif classes[int(box.cls[0].tolist())] == 'no_parking':
            print("No Parking")
            send_servo_command(7)    
        elif classes[int(box.cls[0].tolist())] == 'no_waiting':
            print("No waiting")
            send_servo_command(6)
        elif classes[int(box.cls[0].tolist())] == 'Parking-Sign':
            print("Parking")
            send_servo_command(5)
        # elif classes[int(box.cls[0].tolist())] == 'do_not_u_turn':
        #     print("don't u turn")
        #     send_servo_command(5)    
        elif classes[int(box.cls[0].tolist())] == 'u_turn':
            print("u turn")
            send_servo_command(4)
        # elif classes[int(box.cls[0].tolist())] == 'Round-About':
        #     print("Round About")
        #     send_servo_command(5) 
        
    return frame

        
        


while True:
     # Read a frame from the video stream
    img_resp=urllib.request.urlopen(url)
    imgnp=np.array(bytearray(img_resp.read()),dtype=np.uint8)
    #ret, frame = cap.read()
    im = cv2.imdecode(imgnp,-1)
    annotatedFrame = findObject(im)
    cv2.imshow('Image', annotatedFrame)

    #Remove this part and switch with the above commented code in the actual hardware implemetation
   # ret, frame = cap.read()
  #  annotatedFrame = findObject(frame) 
 #   cv2.imshow('Image', annotatedFrame)

        
    if cv2.waitKey(1) == ord('q'):
        break

cv2.destroyAllWindows()
