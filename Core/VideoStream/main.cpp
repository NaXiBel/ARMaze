#include "main.h"

CameraCV * createCamera() {
	std::cout << "Creating camera..." << std::endl;
	return new CameraCV();
}

void disposeCamera(CameraCV * cam) {
	if(cam != NULL) {
		delete cam;
		cam = NULL;
		std::cout << "Camera deleted." << std::endl;
	}
}

void openStream(CameraCV * cam, int id /* = 0 */) {
	cam->openStream(id);
	std::cout << "Camera stream opened." << std::endl;
}

void displayStream(CameraCV * cam) {
	cam->displayStream();
	std::cout << "Frame displayed." << std::endl;
}

int getWidth(CameraCV * cam) {
	int width = cam->getWidth();
	std::cout << "width : " << width << std::endl;
	return width;
}

int getHeight(CameraCV * cam) {
	int height = cam->getHeigth();
	std::cout << "width : " << height << std::endl;
	return height;
}

uchar * getLiveFrame(CameraCV * cam, int * sizeofMat) {
	return cam->getLiveFrame(sizeofMat);
}
