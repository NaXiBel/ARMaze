// g++ -I"C:\Program Files\opencv\build\include" -L"C:\Program Files\opencv\release\lib" -g -o Test.exe TestStream.cxx -lopencv_core343 -lopencv_imgproc343 -lopencv_highgui343 -lopencv_imgcodecs343 -lopencv_videoio343

#define TEST_CLASS

#ifdef TEST_CLASS
#include "opencv2/opencv.hpp"
#include "../Core.h"
#include "CameraCV.h"
#include "main.h"

using namespace cv;

int main(void) {
	String window_name = "Test class";

	//namedWindow(window_name, WINDOW_AUTOSIZE);

	//int c = waitKey(10);
	Core* core = createCore();
	Calibrator* calibrator = create_calibrator(15, 50);

	bool calibrated = false;

	while(true) {
		//cam->readFrame();
		//Mat fraaame = cam->getFrame();

		core->getCamera()->readFrame();
		imshow(window_name, core->getCamera()->getFrame());
		waitKey(50);
		add_pattern_to_calibrator(calibrator, core);

		if (!calibrated && check_pattern_count(calibrator)) {

			calibrate(calibrator, core);
			cout << "calibrated" << endl;
			get_K(calibrator);
			get_D(calibrator);

		}

		//imshow(window_name, fraaame);
		//c = waitKey(10);
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
