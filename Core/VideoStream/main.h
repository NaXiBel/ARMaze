#pragma once
#ifdef _WIN32
#define DllExport extern "C" __declspec(dllexport)
#else
#define DllExport extern "C"
#endif

#include "CameraCV.h"
#include "../Core.h"
#include "../Homography/Homography/TransformTracking.h"

DllExport CameraCV * createCamera();
DllExport void disposeCamera(CameraCV * cam);
DllExport void openStream(CameraCV * cam, int id);
DllExport void displayStream(CameraCV * cam);
DllExport int getWidth(CameraCV * cam);
DllExport int getHeight(CameraCV * cam);
DllExport uchar * getLiveFrame(CameraCV * cam, int * sizeofMat);

DllExport Core * createCore();
DllExport bool check_build(Core*);
DllExport void build(Core*);
DllExport void init_transform(TransformTracking*, Area*);
DllExport void update_transform(TransformTracking*, Area*);
DllExport void tracking(Core*);
DllExport Area* get_area(Core* core);
DllExport bool check_tracking(Core*);

DllExport Area* create_area();
DllExport Point2d* get_begin_center(Area*, TransformTracking*);
DllExport Point2d* get_end_center(Area*, TransformTracking*);
DllExport vector<Point2d*>* get_wall(Area*, TransformTracking*, int i);
DllExport Point2d* get_point(int j, vector<Point2d*>*);
DllExport int nb_of_walls(Area*);
DllExport int size(vector<Point*>*);
DllExport double get_x(Point2d*);
DllExport double get_y(Point2d*);

DllExport TransformTracking* create_transform_tracking();
DllExport Mat* get_init_rot(TransformTracking*);
DllExport Mat* get_delta_rot(TransformTracking*);
DllExport Mat* get_init_trans(TransformTracking*);
DllExport Mat* get_delta_trans(TransformTracking*);
DllExport double at(int, int, Mat*);
