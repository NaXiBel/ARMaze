#pragma once
#ifdef _WIN32
#define DllExport  extern "C" __declspec(dllexport)
#else
#define DllExport extern "C"
#endif

#include "CameraCV.h"

DllExport CameraCV * createCamera();
DllExport void disposeCamera(CameraCV * cam);
DllExport void openStream(CameraCV * cam, int id);
DllExport void displayStream(CameraCV * cam);
DllExport int getWidth(CameraCV * cam);
DllExport int getHeight(CameraCV * cam);
DllExport byte * getLiveFrame(CameraCV * cam);
