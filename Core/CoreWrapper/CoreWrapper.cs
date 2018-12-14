using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;

namespace Wrapper {

    public class CoreWrapper {
        public struct embededFunctions {
            const string dllpath = @".\VideoStream.dll";
            //const string dllpath = @"C:\Users\alexm\Documents\ARMaze\Core\x64\Debug\VideoStream.dll";

            [DllImport(dllpath, EntryPoint = "createCamera")] static public extern IntPtr CreateCameraInput();
            [DllImport(dllpath, EntryPoint = "disposeCamera")] static public extern void DisposeCameraInput(IntPtr pCam);
            [DllImport(dllpath, EntryPoint = "openStream")] static public extern void OpenStream(IntPtr pCam, int id = 0);
            [DllImport(dllpath, EntryPoint = "closeStream")] static public extern void CloseStream(IntPtr pCam);
            [DllImport(dllpath, EntryPoint = "displayStream")] static public extern void DisplayStream(IntPtr pCam);
            [DllImport(dllpath, EntryPoint = "getLiveFrame")] static public extern IntPtr GetLiveFrame(IntPtr pCam, out int sizeofMat);
            [DllImport(dllpath, EntryPoint = "getWidth")] static public extern int GetWidth(IntPtr pCam);
            [DllImport(dllpath, EntryPoint = "getHeight")] static public extern int GetHeight(IntPtr pCam);

            [DllImport(dllpath, EntryPoint = "create_area")] static public extern IntPtr CreateArea();
            [DllImport(dllpath, EntryPoint = "get_begin_center")] static public extern IntPtr GetBeginCenter(IntPtr area, IntPtr transformTracking);
            [DllImport(dllpath, EntryPoint = "get_end_center")] static public extern IntPtr GetEndCenter(IntPtr area, IntPtr transformTracking);
            [DllImport(dllpath, EntryPoint = "get_wall")] static public extern IntPtr GetWall(IntPtr area, IntPtr transformTracking, int i);
            [DllImport(dllpath, EntryPoint = "get_point")] static public extern IntPtr GetPoint(int j, IntPtr vectorPoint);
            [DllImport(dllpath, EntryPoint = "nb_of_walls")] static public extern int NbOfWalls(IntPtr area);
            [DllImport(dllpath, EntryPoint = "size")] static public extern int Size(IntPtr vectorPoint);
            [DllImport(dllpath, EntryPoint = "get_x")] static public extern double GetX(IntPtr point2d);
            [DllImport(dllpath, EntryPoint = "get_y")] static public extern double GetY(IntPtr point2d);

            [DllImport(dllpath, EntryPoint = "createCore")] static public extern IntPtr CreateCore();
            [DllImport(dllpath, EntryPoint = "video")] static public extern void Video(IntPtr core);
            [DllImport(dllpath, EntryPoint = "check_build")] static public extern bool CheckBuild(IntPtr core);
            [DllImport(dllpath, EntryPoint = "build")] static public extern void Build(IntPtr core);
            [DllImport(dllpath, EntryPoint = "getCameraCV")] static public extern IntPtr getCoreCamera(IntPtr core);
            [DllImport(dllpath, EntryPoint = "setCameraCV")] static public extern void setCoreCamera(IntPtr core, IntPtr camera);
            [DllImport(dllpath, EntryPoint = "start")] static public extern void Start(IntPtr core);

            [DllImport(dllpath, EntryPoint = "create_calibrator")] static public extern IntPtr CreateCalibrator(int image_count, int square_size);
            [DllImport(dllpath, EntryPoint = "add_pattern_to_calibrator")] static public extern void AddPatternToCalibrator(IntPtr calibrator, IntPtr cameraCV);
            [DllImport(dllpath, EntryPoint = "check_pattern_count")] static public extern bool CheckPatternCount(IntPtr calibrator);
            [DllImport(dllpath, EntryPoint = "calibrate")] static public extern bool Calibrate(IntPtr calibrator, IntPtr cameraCV);
            /*
            DllExport Mat* get_K(Calibrator*);
            DllExport Mat* get_D(Calibrator*);
            DllExport void init_transform(TransformTracking*, Area*, Mat*, Mat*);
            DllExport void init_transform_import_KD(TransformTracking*, Area*,
                double K00, double K01, double K02,
                double K10, double K11, double K12,
                double K20, double K21, double K22,
                double D0, double D1, double D2, double D4);
            */
            [DllImport(dllpath, EntryPoint = "init_transform")] static public extern void InitTransform(IntPtr tranformTracking, IntPtr area, IntPtr K, IntPtr D);
            [DllImport(dllpath, EntryPoint = "update_transform")] static public extern void UpdateTransform(IntPtr tranformTracking, IntPtr area);
            [DllImport(dllpath, EntryPoint = "tracking")] static public extern void Tracking(IntPtr core);
            [DllImport(dllpath, EntryPoint = "get_area")] static public extern IntPtr GetArea(IntPtr core);
            [DllImport(dllpath, EntryPoint = "check_tracking")] static public extern bool CheckTracking(IntPtr core);

            [DllImport(dllpath, EntryPoint = "create_transform_tracking")] static public extern IntPtr CreateTransformTracking();
            [DllImport(dllpath, EntryPoint = "get_init_rot")] static public extern IntPtr GetInitRot(IntPtr transformTracking);
            [DllImport(dllpath, EntryPoint = "get_delta_rot")] static public extern IntPtr GetDeltaRot(IntPtr transformTracking);
            [DllImport(dllpath, EntryPoint = "get_init_trans")] static public extern IntPtr GetInitTrans(IntPtr transformTracking);
            [DllImport(dllpath, EntryPoint = "get_delta_trans")] static public extern IntPtr GetDeltaTrans(IntPtr transformTracking);
            [DllImport(dllpath, EntryPoint = "at")] static public extern double At(int x, int y, IntPtr mat);

        }

        private static CoreWrapper instance = null;
        public bool FinishedBuild;
        private IntPtr camera;
        private IntPtr core;
        private IntPtr area;
        private IntPtr tranformTracking;
        private IntPtr K;
        private IntPtr D;

        private CoreWrapper() { }

        static public CoreWrapper GetInstance() {
            if(instance == null) {
                instance = new CoreWrapper();
            }

            return instance;
        }

        /*** CameraCV Wrapping ***/
        public void InitCamera() {
            this.camera = embededFunctions.CreateCameraInput();
        }
        public void DisposeCamera() {
            embededFunctions.DisposeCameraInput(this.camera);
        }
        public void OpenVideoStream(int id = 0) {
            embededFunctions.OpenStream(this.camera, id);
        }
        public void CloseVideoStream() {
            embededFunctions.CloseStream(this.camera);
        }
        public void DisplayCameraStream() {
            embededFunctions.DisplayStream(this.camera);
        }
        public byte[] GetCameraFrame() {
            IntPtr buffer = embededFunctions.GetLiveFrame(this.camera, out int sizeofMat);
            byte[] bytes = new byte[sizeofMat];
            Marshal.Copy(buffer, bytes, 0, sizeofMat);

            return bytes;
        }
        public int GetFrameWidth() {
            return embededFunctions.GetWidth(this.camera);
        }
        public int GetFrameHeight() {
            return embededFunctions.GetHeight(this.camera);
        }

        public double[] GetBeginCenter() {
            IntPtr beginPtr = embededFunctions.GetBeginCenter(area, tranformTracking);
            double[] beginDouble = new double[2];
            beginDouble[0] = embededFunctions.GetX(beginPtr);
            beginDouble[1] = embededFunctions.GetY(beginPtr);
            return beginDouble;
        }
        public double[] GetEndCenter() {
            IntPtr endPtr = embededFunctions.GetEndCenter(area, tranformTracking);
            double[] endDouble = new double[2];
            endDouble[0] = embededFunctions.GetX(endPtr);
            endDouble[1] = embededFunctions.GetY(endPtr);
            return endDouble;
        }
        public List<double[,]> GetWall() {
            List<double[,]> walls = new List<double[,]>();
            for(int i = 0; i < embededFunctions.NbOfWalls(area); ++i) {
                IntPtr wallPtr = embededFunctions.GetWall(area, tranformTracking, i);
                double[,] wallDouble = new double[2, 2];

                for(int j = 0; j < 2; ++j) {
                    wallDouble[j, 0] = embededFunctions.GetX(embededFunctions.GetPoint(j, wallPtr));
                    wallDouble[j, 1] = embededFunctions.GetY(embededFunctions.GetPoint(j, wallPtr));
                }
                walls.Add(wallDouble);
            }
            return walls;
        }

        /*** Core Wrapping ***/
        public void InitCore() {
            this.core = embededFunctions.CreateCore();
            this.camera = embededFunctions.getCoreCamera(this.core);
            this.FinishedBuild = false;
        }
        public void Video() {
            embededFunctions.Video(core);
        }
        public bool CheckBuid() {
            return embededFunctions.CheckBuild(this.core);
        }
        public void Build() {
            embededFunctions.Build(this.core);
            area = embededFunctions.GetArea(camera);
        }
        public IntPtr GetCoreCamera() {
            return this.camera;
        }
        public void SetCoreCamera(IntPtr cam) {
            embededFunctions.setCoreCamera(this.core, cam);
        }
        public void Start() {
            embededFunctions.Start(this.core);
        }

        public void CalibrateCamera() {
            //embededFunctions.Calibrate(area, camera, K, D);
        }

        public void InitTransform() {
            tranformTracking = embededFunctions.CreateTransformTracking();
            embededFunctions.InitTransform(tranformTracking, area, K, D);
        }
        public void UpdateTranform() {
            embededFunctions.UpdateTransform(tranformTracking, area);
        }
        public void Tracking() {
            embededFunctions.Tracking(this.core);
            area = embededFunctions.GetArea(camera);
        }
        public bool CheckTracking() {
            return embededFunctions.CheckTracking(camera);
        }

        public double[] GetInitRot() {
            double[] rot = new double[3];
            IntPtr matRot = embededFunctions.GetInitRot(tranformTracking);
            for(int i = 0; i < 3; i++) {
                rot[i] = embededFunctions.At(i, 0, matRot);
            }
            return rot;
        }
        public double[] GetInitTrans() {
            double[] trans = new double[3];
            IntPtr matTrans = embededFunctions.GetInitTrans(tranformTracking);
            for(int i = 0; i < 3; i++) {
                trans[i] = embededFunctions.At(i, 0, matTrans);
            }
            return trans;
        }
        public double[] GetDeltaRot() {
            double[] rot = new double[3];
            IntPtr matRot = embededFunctions.GetDeltaRot(tranformTracking);
            for(int i = 0; i < 3; i++) {
                rot[i] = embededFunctions.At(i, 0, matRot);
            }
            return rot;
        }
        public double[] GetDeltaTrans() {
            double[] trans = new double[3];
            IntPtr matTrans = embededFunctions.GetDeltaTrans(tranformTracking);
            for(int i = 0; i < 3; i++) {
                trans[i] = embededFunctions.At(i, 0, matTrans);
            }
            return trans;
        }

        static void Main(string[] args) {
            CoreWrapper wrap = CoreWrapper.GetInstance();
            wrap.InitCore();
            while(true) {
                ConsoleKey input = Console.ReadKey().Key;
                if(input == ConsoleKey.I)
                    wrap.InitCamera();
                else if(input == ConsoleKey.S)
                    wrap.SetCoreCamera(wrap.camera);
                else if(input == ConsoleKey.O)
                    wrap.OpenVideoStream(0);
                else if(input == ConsoleKey.C) 
                    wrap.CloseVideoStream();
                else if(input == ConsoleKey.D)
                    wrap.DisposeCamera();
                else if(input == ConsoleKey.Q)
                    break;
                else {
                    byte[] test = wrap.GetCameraFrame();
                    Console.WriteLine(test[0] + " " + test[test.Length - 1]);
                }
            }

            /******/

            //CoreWrapper wrap = CoreWrapper.GetInstance();
            //wrap.InitCore();
            //wrap.OpenVideoStream(0);
            ////wrap.Start();

            //while(!wrap.CheckBuid())
            //    wrap.Build();

            //wrap.InitTransform();
            //do {
            //    wrap.Tracking();
            //    wrap.UpdateTranform();

            //    double[] rot = wrap.GetDeltaRot();
            //    for(int i = 0; i < 3; i++) {
            //        Console.Write(rot[i] + " ");
            //    }
            //} while(wrap.CheckTracking());

            //Console.ReadKey();
        }
    }
}
