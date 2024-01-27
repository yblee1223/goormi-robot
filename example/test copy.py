import cv2
import mediapipe as mp
import matplotlib.pyplot as plt

# MediaPipe Face Mesh 모델을 로드합니다.
mp_face_mesh = mp.solutions.face_mesh
face_mesh = mp_face_mesh.FaceMesh()

# Webcam을 초기화합니다.
cap = cv2.VideoCapture('/Users/iyongbin/Repository/goormi-robot/example/mediapipe/im0.png')

ret, frame = cap.read()

# 얼굴 landmark 감지
result = face_mesh.process(frame)

if result.multi_face_landmarks:
    for landmarks in result.multi_face_landmarks:
        for point in landmarks.landmark:
            height, width, _ = frame.shape
            cx, cy = int(point.x * width), int(point.y * height)
            cv2.circle(frame, (cx, cy), 2, (0, 255, 0), -1)

# 결과를 화면에 표시
plt.imshow(frame)


