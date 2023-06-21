import cv2
import numpy as np
import tensorflow as tf
from keras.models import load_model
import serial
from time import sleep
#import keyboard

# Define the output classes
output_class = ["batteries", "clothes", "e-waste", "glass", "light blubs", "metal", "organic", "paper", "plastic"]

# Establish a serial connection to the Arduino
PORT = 'COM4 '  # Replace with the appropriate port for your Arduino
BUADRATE = 9600
robot = serial.Serial(PORT, BUADRATE)  # connect robot

# Load the trained model

mod = load_model("C:/Users/ranya/Downloads/classifyWaste (1)_rana.h5")

# Initialize the camera
cap = cv2.VideoCapture("http://10.160.161.111:8080/video") #نجرب الموبيل بقي

while True:
    # Capture a frame from the camera
    ret, frame = cap.read()

    # Check if the frame was successfully read
    if not ret:
        continue

    # Preprocess the image
    img = cv2.resize(frame, (224, 224))
    img = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)
    img = np.expand_dims(img, axis=0)

    # Make a prediction
    prediction = np.argmax(mod.predict(img))

    # Display the prediction and the image
    cv2.putText(frame, f"Prediction: {output_class[prediction]}", (10, 30), cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 255, 0), 2)
    cv2.imshow('frame', frame)

    # Send commands to the robot based on the prediction
    if prediction == 7 or prediction == 8 :
        robot.write(b'u')
        print('open fan')
        #نزود الوقت اللي هايكون فيها في case دي
    else:
        robot.write(b'f')
        print('close fan')

    # Check for 'q' key press to stop the robot
    # command = input('Enter command: ')
    # if command == 'f':
    #     robot.write(b'q')  # Send the 's' command to stop the robot
    #     print('Stopping robot')
    #     break
    # command = input('Enter command: ')
    # if command == 'f':
    #      robot.write(b'q')  # Send the 's' command to stop the robot
    #      print('Stopping robot')
    #      break

    # Press 'q' to exit the loop
    if cv2.waitKey(50) & 0xFF == ord('q'):
       #عايزين نجرب اننا نحطها تحت خالص علشان نشوف الروبوت هايوقف ولا لأ
        break


# Release the camera and close the window
cap.release()
cv2.destroyAllWindows()
# Close the serial connection to the Arduino
robot.close()