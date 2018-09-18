#pragma once
#ifdef _WIN32
#define DllExport  extern "C" __declspec(dllexport)
#else
#define DllExport extern "C"
#endif

#include "CameraCV.h"
#include "TestDLL.h"

DllExport CameraCV * createCamera();
DllExport void disposeCamera(CameraCV * cam);
DllExport void openStream(CameraCV * cam);
DllExport byte * getLiveFrame(CameraCV * cam);

DllExport TestDLL * createTest();
