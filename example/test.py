import cv2
import mediapipe as mp

# MediaPipe Face Mesh 모델을 로드합니다.
mp_face_mesh = mp.solutions.face_mesh
face_mesh = mp_face_mesh.FaceMesh()

# Webcam을 초기화합니다.
cap = cv2.VideoCapture(0)

while cap.isOpened():
    ret, frame = cap.read()
    if not ret:
        break

    # 얼굴 landmark 감지
    result = face_mesh.process(frame)

    if result.multi_face_landmarks:
        for landmarks in result.multi_face_landmarks:
            for point in landmarks.landmark:
                height, width, _ = frame.shape
                cx, cy = int(point.x * width), int(point.y * height)
                cv2.circle(frame, (cx, cy), 2, (0, 255, 0), -1)

    # 결과를 화면에 표시
    cv2.imshow("Face Landmarks", frame)

    if cv2.waitKey(1) & 0xFF == 27:  # 'ESC' 키를 누르면 종료
        break

# 종료 시 자원 해제
cap.release()
cv2.destroyAllWindows()
