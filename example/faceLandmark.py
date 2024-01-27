import cv2
import mediapipe as mp

# Mediapipe의 Face 모듈을 사용하기 위한 초기화
mp_face_detection = mp.solutions.face_detection
mp_drawing = mp.solutions.drawing_utils
face_detection = mp_face_detection.FaceDetection()

# 웹캠에서 영상을 받아오기
cap = cv2.VideoCapture(0)

while cap.isOpened():
    # 프레임 읽기
    ret, frame = cap.read()
    if not ret:
        break

    # BGR을 RGB로 변환
    rgb_frame = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)

    # face landmark detection 수행
    results = face_detection.process(rgb_frame)

    # 결과가 있을 경우 처리
    if results.detections:
        for detection in results.detections:
            # bounding box 좌표 추출
            bboxC = detection.location_data.relative_bounding_box
            print(bboxC)
            ih, iw, _ = frame.shape
            bbox = int(bboxC.xmin * iw), int(bboxC.ymin * ih), \
                   int(bboxC.width * iw), int(bboxC.height * ih)

            # 얼굴 주변에 사각형 그리기
            cv2.rectangle(frame, bbox, (0, 255, 0), 2)

            # 얼굴 랜드마크 그리기
            mp_drawing.draw_landmarks(frame, detection.landmark, mp_face_detection.FACE_CONNECTIONS)

    # 화면에 결과 출력
    cv2.imshow('Face Landmark Detection', frame)

    # 'q' 키를 누르면 종료
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# 사용한 자원 해제
cap.release()
cv2.destroyAllWindows()
