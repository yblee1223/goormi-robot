import cv2
import numpy as np

# from sklearn.model_selection import train_test_split

import torchvision.transforms as transforms
import torchvision.models as models
import torch
from torch import nn
import torch.nn.functional as F
import torchvision.transforms as tt

# model
class resnet(nn.Module):
    def __init__(self, is_freezed=False):
        super(resnet, self).__init__()
        self.model = models.resnet18(weights='IMAGENET1K_V1')
        if is_freezed:
            for child in self.model.children():
                child.requires_grad = False
        self.model.fc = nn.Sequential(
            nn.Linear(self.model.fc.in_features, 256),
            nn.Linear(256, 5)
        )
    def forward(self, x):
        return self.model(x)
    
# detection
def conv_block(in_channels, out_channels, pool=False):
    layers = [
        nn.Conv2d(in_channels, out_channels, kernel_size=3, padding=1),
        nn.BatchNorm2d(out_channels),
        nn.ELU(inplace=True),
    ]
    if pool:
        layers.append(nn.MaxPool2d(2))
    return nn.Sequential(*layers)


def conv_block(in_channels, out_channels, pool=False):
    layers = [
        nn.Conv2d(in_channels, out_channels, kernel_size=3, padding=1),
        nn.BatchNorm2d(out_channels),
        nn.ReLU(inplace=True),
    ]
    if pool:
        layers.append(nn.MaxPool2d(2))
    return nn.Sequential(*layers)

# pretrained model import

device = torch.device('cpu')
model = resnet(is_freezed=True)
model.load_state_dict(torch.load('/Users/iyongbin/Repository/goormi-robot/model/model_65.pth', map_location=device))
face_classifier = cv2.CascadeClassifier("/Users/iyongbin/Repository/goormi-robot/model/haarcascade_frontalface_default.xml")

labels = ['angry', 'happy', 'neutral', 'sad', 'surprised']

# video capture

cap = cv2.VideoCapture(0)

while True:
    # Grab a single frame of video
    ret, frame = cap.read()
    frame = cv2.flip(frame, 1)
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    faces = face_classifier.detectMultiScale(gray, 1.3, 5)

    for (x, y, w, h) in faces:
        cv2.rectangle(frame, (x, y), (x + w, y + h), (255, 0, 0), 2)
        roi_rgb = frame[y : y + h, x : x + w]
        roi_rgb = cv2.resize(roi_rgb, (48, 48), interpolation=cv2.INTER_AREA)
        print(roi_rgb.shape)

        if np.sum([roi_rgb]) != 0:
            roi = tt.functional.to_pil_image(roi_rgb)
            # roi = tt.functional.to_grayscale(roi)
            roi = tt.ToTensor()(roi).unsqueeze(0)

            # make a prediction on the ROI
            tensor = model(roi)
            pred = torch.max(tensor, dim=1)[1].tolist()
            print(pred[0])
            label = labels[pred[0]]

            label_position = (x, y)
            cv2.putText(
                frame,
                label,
                label_position,
                cv2.FONT_HERSHEY_COMPLEX,
                2,
                (0, 255, 0),
                3,
            )
        else:
            cv2.putText(
                frame,
                "No Face Found",
                (20, 60),
                cv2.FONT_HERSHEY_COMPLEX,
                2,
                (0, 255, 0),
                3,
            )

    cv2.imshow("Emotion Detector", frame)

    if cv2.waitKey(1) & 0xFF == ord("q"):
        break

cap.release()
cv2.destroyAllWindows()