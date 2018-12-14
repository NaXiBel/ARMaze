// g++ -I"C:\Program Files\opencv\build\include" -L"C:\Program Files\opencv\release\lib" -g -o Test.exe TestStream.cxx -lopencv_core343 -lopencv_imgproc343 -lopencv_highgui343 -lopencv_imgcodecs343 -lopencv_videoio343

#define TEST_CORE

#ifdef TEST_CORE
#include "opencv2/opencv.hpp"
#include "../Core.h"
#include "CameraCV.h"
#include "main.h"

using namespace cv;

int test(void) {
	String window_name = "Test class";
	Core* core = createCore();
	CameraCV* cameraCv = getCameraCV(core);

	while(!check_build(core)) {
		build(core);
		Mat frame = core->get_camera()->getFrame();
		imshow("ROT", frame);
		waitKey(10);
	}

	TransformTracking* transformTracking = create_transform_tracking();
	init_transform_default(transformTracking, core->getArea());

	cout << "init rot : " << transformTracking->get_init_rot() << endl;

	while (check_tracking(core)) {
		tracking(core);
		update_transform(transformTracking, core->getArea());
		cout << "delta rot : " << transformTracking->get_delta_rot() << endl;
		Mat frame = core->get_camera()->getFrame();
		imshow("ROT", frame);
		waitKey(10);
	}

	return 0;
}
#else 
#include "opencv2/opencv.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;

/* Global variables */
String window_name = "Capture";

/* @function main */
int main(void) {
    VideoCapture capture;
    Mat frame;
    
    namedWindow(window_name ,WINDOW_AUTOSIZE);
    
    // Read the video stream
    capture.open(1);
    if(!capture.isOpened()) { 
        printf("--(!)Error opening video capture\n"); 
        return -1; 
    }
    
    capture.set(CV_CAP_PROP_FRAME_WIDTH , 640); 
    capture.set(CV_CAP_PROP_FRAME_HEIGHT , 480); 
    capture.set (CV_CAP_PROP_FOURCC, CV_FOURCC('B', 'G', 'R', '3'));

    while(capture.read(frame)) {
        if(frame.empty()) {
            printf("(!) No captured frame -- Break!");
            break;
        }

        imshow(window_name, frame);
        int c = waitKey(10);
        if((char)c == 'q') { 
            break; 
        }
    }
	return 0;
}
#endif
