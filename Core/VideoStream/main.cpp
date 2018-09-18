#include "main.h"

CameraCV * createCamera() {
	std::cout << " Creating camera..." << std::endl;
	return new CameraCV();
}

void disposeCamera(CameraCV * cam) {
	if(cam != NULL) {
		delete cam;
		cam = NULL;
		std::cout << "Camera deleted." << std::endl;
	}
}

void openStream(CameraCV * cam) {
	cam->openStream();
	std::cout << "Camera stream opened." << std::endl;
}

void displayStream(CameraCV * cam) {
	cam->displayStream();
	std::cout << "Frame displayed." << std::endl;
}

byte * getLiveFrame(CameraCV * cam) {
	return cam->getLiveFrame();
}

