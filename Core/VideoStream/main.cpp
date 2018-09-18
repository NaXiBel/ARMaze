#include "main.h"

DllExport CameraCV * createCamera() {
	return new CameraCV();
}

DllExport void disposeCamera(CameraCV * cam) {
	if(cam != NULL) {
		delete cam;
		cam = NULL;
	}
}

DllExport void openStream(CameraCV * cam) {
	cam->openStream();
}

DllExport byte * getLiveFrame(CameraCV * cam) {
	return cam->getLiveFrame();
}

DllExport TestDLL * createTest() {
	return new TestDLL();
}
