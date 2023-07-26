import cv2

print("Displaying webcam using opencv - press escape to exit")

cv2_webcam_capture = cv2.VideoCapture(0) # 0: first webcam in device list

while cv2_webcam_capture.isOpened():
    success, cv2_webcam_image = cv2_webcam_capture.read()

    if success:
        cv2.imshow('image', cv2_webcam_image)

    if cv2.waitKey(1) == 27: 
        break  # esc to quit