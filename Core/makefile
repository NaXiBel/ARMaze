OPENCV_LIBS = -L/usr/local/Cellar/opencv/3.4.3_1/lib -L/usr/local/Cellar/opencv/3.4.3_1/lib -lopencv_stitching -lopencv_superres -lopencv_videostab -lopencv_aruco -lopencv_bgsegm -lopencv_bioinspired -lopencv_ccalib -lopencv_dnn_objdetect -lopencv_dpm -lopencv_face -lopencv_photo -lopencv_fuzzy -lopencv_hfs -lopencv_img_hash -lopencv_line_descriptor -lopencv_optflow -lopencv_reg -lopencv_rgbd -lopencv_saliency -lopencv_sfm -lopencv_stereo -lopencv_structured_light -lopencv_phase_unwrapping -lopencv_surface_matching -lopencv_tracking -lopencv_datasets -lopencv_dnn -lopencv_plot -lopencv_xfeatures2d -lopencv_shape -lopencv_video -lopencv_ml -lopencv_ximgproc -lopencv_calib3d -lopencv_features2d -lopencv_highgui -lopencv_videoio -lopencv_flann -lopencv_xobjdetect -lopencv_imgcodecs -lopencv_objdetect -lopencv_xphoto -lopencv_imgproc -lopencv_core -std=c++11

VideoStream: ./VideoStream/TestStream.cpp main.o CameraCV.o Calibrator.o Core.o Area.o TransformTracking.o MazeTransform.o
	g++ -dynamiclib -o VideoStream.dylib ./VideoStream/TestStream.cpp main.o CameraCV.o Calibrator.o Core.o Area.o TransformTracking.o MazeTransform.o $(OPENCV_LIBS)

main.o: ./VideoStream/main.h ./VideoStream/main.cpp ./VideoStream/CameraCV.h Core.h ./Homography/Homography/TransformTracking.h ./VideoStream/Calibrator.h
	g++ -c ./VideoStream/main.cpp $(OPENCV_LIBS)

CameraCV.o: ./VideoStream/CameraCV.h ./VideoStream/CameraCV.cpp 
	g++ -c ./VideoStream/CameraCV.cpp $(OPENCV_LIBS)

Calibrator.o: ./VideoStream/Calibrator.h ./VideoStream/Calibrator.cpp
	g++ -c ./VideoStream/Calibrator.cpp $(OPENCV_LIBS)

Core.o: Core.h Core.cpp Area.h ./Homography/Homography/TransformTracking.h ./VideoStream/CameraCV.h
	g++ -c Core.cpp $(OPENCV_LIBS)

Area.o: Area.h Area.cpp ./Homography/Homography/TransformTracking.h
	g++ -c Area.cpp $(OPENCV_LIBS)

TransformTracking.o: ./Homography/Homography/TransformTracking.h ./Homography/Homography/TransformTracking.cpp ./Homography/Homography/MazeTransform.h
	g++ -c ./Homography/Homography/TransformTracking.cpp $(OPENCV_LIBS)

MazeTransform.o: ./Homography/Homography/MazeTransform.h ./Homography/Homography/MazeTransform.cpp
	g++ -c ./Homography/Homography/MazeTransform.cpp $(OPENCV_LIBS)