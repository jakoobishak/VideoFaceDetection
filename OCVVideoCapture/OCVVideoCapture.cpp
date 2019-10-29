#include "pch.h"
#include <iostream>
#include <stdlib.h>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void detectAndDisplay(Mat frame);

CascadeClassifier FaceDetection;
String windowName = "Face Detection Video Player";

int main() {

	VideoCapture cap("C:\\Users\\Jakoob\\Documents\\KodProjekt\\OCVVideoCapture\\video2.mp4");
	
	
	if (!FaceDetection.load("C:\\Users\\Jakoob\\Documents\\opencv\\sources\\data\\haarcascades\\haarcascade_frontalface_alt.xml")) {
		cout << "\n File is not loaded correctly";
		exit(0);
	}

	if (!cap.isOpened()) {
		cout << "\n File not found";
		cin.get();
		exit(0);
	}

	namedWindow(windowName, WINDOW_NORMAL);

	while (1) {
		Mat frame;
		bool bSuccess = cap.read(frame);
		
		if (bSuccess == false) {
			cout << "\n Video has ended";
			break;
		}

		detectAndDisplay(frame);

		if (waitKey(10) == 27){
			cout << "\n Esc key is pressed. Stopping the video.";
			break;
		}
	}

	return 0;
}

void detectAndDisplay(Mat frame) {

	vector<Rect> faces;
	Mat frame_gray;

	cvtColor(frame, frame_gray, COLOR_BGR2GRAY);
	equalizeHist(frame_gray, frame_gray);

	FaceDetection.detectMultiScale(frame_gray, faces, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size(30, 30));

	for (size_t i = 0; i < faces.size(); i++) {
		Point pt1(faces[i].x, faces[i].y);
		Point pt2((faces[i].x + faces[i].height), (faces[i].y + faces[i].width));
		rectangle(frame, pt1, pt2, Scalar(0, 0, 255), 2, 7, 0);
	}
	
	imshow(windowName, frame);
}