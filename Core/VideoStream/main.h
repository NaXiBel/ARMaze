#pragma once
#ifdef _WIN32
#define DllExport extern "C" __declspec(dllexport)
#else
#define DllExport extern "C"
#endif

#include "CameraCV.h"
#include "../Core.h"
#include "../Homography/Homography/TransformTracking.h"
#include "Calibrator.h"

/*** CameraCV functions ***/
DllExport CameraCV * createCamera();
DllExport void disposeCamera(CameraCV * cam);
DllExport void openStream(CameraCV * cam, int id);
DllExport void displayStream(CameraCV * cam);
DllExport int getWidth(CameraCV * cam);
DllExport int getHeight(CameraCV * cam);
DllExport uchar * getLiveFrame(CameraCV * cam, int * sizeofMat);

/*** Core functions ***/
DllExport Core * createCore();
DllExport bool check_build(Core*);
DllExport void build(Core*);
DllExport CameraCV * getCameraCV(Core*);
DllExport void setCameraCV(Core*, CameraCV*);
DllExport void setCannyThreshold(Core* core, int thresh);
DllExport void setCannyThreshold2(Core* core, int thresh);
DllExport void setKernelThreshold1(Core* core, int thresh);
DllExport void setKernelThreshold2(Core* core, int thresh);
DllExport void start(Core*);

// calibration
DllExport Calibrator* create_calibrator(int image_count, int square_size);
DllExport void add_pattern_to_calibrator(Calibrator*, Core*);
DllExport bool check_pattern_count(Calibrator*);
DllExport void calibrate(Calibrator*, Core*);
DllExport Mat* get_K(Calibrator*);
DllExport Mat* get_D(Calibrator*);

DllExport void init_transform_default(TransformTracking*, Area*);
DllExport void init_transform(TransformTracking*, Area*, Mat*, Mat*);
DllExport void init_transform_import_KD(TransformTracking*, Area*, 
	double K00, double K01, double K02, 
	double K10, double K11, double K12, 
	double K20, double K21, double K22,
	double D0, double D1, double D2, double D3, double D4, double D5, double D6, double D7);

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
