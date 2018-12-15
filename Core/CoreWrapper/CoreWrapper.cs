using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;

namespace Wrapper {

    public class CoreWrapper {
        public struct embededFunctions {
            const string dllpath = @".\VideoStream.dll";

            [DllImport(dllpath, EntryPoint = "createCamera")] static public extern IntPtr CreateCameraInput();
            [DllImport(dllpath, EntryPoint = "disposeCamera")] static public extern void DisposeCameraInput(IntPtr pCam);
            [DllImport(dllpath, EntryPoint = "openStream")] static public extern bool OpenStream(IntPtr pCam, int id = 0);
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
            [DllImport(dllpath, EntryPoint = "calibrate")] static public extern void Calibrate(IntPtr area, IntPtr cameraCV, IntPtr K, IntPtr D);
            [DllImport(dllpath, EntryPoint = "check_build")] static public extern bool CheckBuild(IntPtr core);
            [DllImport(dllpath, EntryPoint = "build")] static public extern void Build(IntPtr core);
            [DllImport(dllpath, EntryPoint = "getCameraCV")] static public extern IntPtr getCoreCamera(IntPtr core);
            [DllImport(dllpath, EntryPoint = "setCameraCV")] static public extern void setCoreCamera(IntPtr core, IntPtr camera);
            [DllImport(dllpath, EntryPoint = "setCannyThreshold")] static public extern void setCannyThreshold(IntPtr core, int thresh);
            [DllImport(dllpath, EntryPoint = "setCannyThreshold2")] static public extern void setCannyThreshold2(IntPtr core, int thresh);
            [DllImport(dllpath, EntryPoint = "setKernelThreshold1")] static public extern void setKernelThreshold1(IntPtr core, int thresh);
            [DllImport(dllpath, EntryPoint = "setKernelThreshold2")] static public extern void setKernelThreshold2(IntPtr core, int thresh);
            [DllImport(dllpath, EntryPoint = "start")] static public extern void Start(IntPtr core);

            [DllImport(dllpath, EntryPoint = "create_calibrator")] static public extern IntPtr CreateCalibrator(int image_count, int square_size);
            [DllImport(dllpath, EntryPoint = "add_pattern_to_calibrator")] static public extern void AddPatternToCalibrator(IntPtr calibrator, IntPtr core);
            [DllImport(dllpath, EntryPoint = "check_pattern_count")] static public extern bool CheckPatternCount(IntPtr calibrator);
            [DllImport(dllpath, EntryPoint = "calibrate")] static public extern void Calibrate(IntPtr calibrator, IntPtr core);
            [DllImport(dllpath, EntryPoint = "get_K")] static public extern IntPtr GetK(IntPtr calibrator);
            [DllImport(dllpath, EntryPoint = "get_D")] static public extern IntPtr GetD(IntPtr calibrator);
            [DllImport(dllpath, EntryPoint = "init_transform_import_KD")]
            static public extern void InitTransformKD(IntPtr tranformTracking, IntPtr area, 
                double K00, double K01, double K02,
                double K10, double K11, double K12,
                double K20, double K21, double K22,
                double D0, double D1, double D2, double D3, double D4, double D5, double D6, double D7);
            [DllImport(dllpath, EntryPoint = "init_transform")] static public extern void InitTransform(IntPtr tranformTracking, IntPtr area, IntPtr K, IntPtr D);
            [DllImport(dllpath, EntryPoint = "init_transform_default")] static public extern void InitTransformDefault(IntPtr transformTracking, IntPtr area);
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
        private IntPtr calibrator;
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

        public double[] GetEndCenter()
        {
            IntPtr endPtr = embededFunctions.GetEndCenter(area, tranformTracking);
            double[] endDouble = new double[2];
            endDouble[0] = embededFunctions.GetX(endPtr);
            endDouble[1] = embededFunctions.GetY(endPtr);
            return endDouble;
        }

        public double[] GetBeginCenter()
        {
            IntPtr beginPtr = embededFunctions.GetBeginCenter(area, tranformTracking);
            double[] beginDouble = new double[2];
            beginDouble[0] = embededFunctions.GetX(beginPtr);
            beginDouble[1] = embededFunctions.GetY(beginPtr);
            return beginDouble;
        }

        public List<double[,]> GetWall()
        {
            List<double[,]> walls = new List<double[,]>();
            for (int i = 0; i < embededFunctions.NbOfWalls(area); ++i)
            {
                IntPtr wallPtr = embededFunctions.GetWall(area, tranformTracking, i);
                double[,] wallDouble = new double[2, 2];

                for (int j = 0; j < 2; ++j)
                {
                    wallDouble[j, 0] = embededFunctions.GetX(embededFunctions.GetPoint(j, wallPtr));
                    wallDouble[j, 1] = embededFunctions.GetY(embededFunctions.GetPoint(j, wallPtr));
                }
                walls.Add(wallDouble);
            }
            return walls;
        }
        
        public void InitCamera() {
            this.camera = embededFunctions.CreateCameraInput();
        }

        public void CreateCalibrator()
        {
            calibrator = embededFunctions.CreateCalibrator(15, 50);
        }

        public void AddPatternToCalibrator()
        {
            embededFunctions.AddPatternToCalibrator(calibrator, core);
        }

        public bool CheckCalibrator()
        {
            return embededFunctions.CheckPatternCount(calibrator);
        }

        public void Calibrate()
        {
            embededFunctions.Calibrate(calibrator, core);
            K = embededFunctions.GetK(calibrator);
            D = embededFunctions.GetD(calibrator);
        }

        public double[,] GetK()
        {
            double[,] res = new double[3, 3]
            {
                {embededFunctions.At(0,0,K), embededFunctions.At(0,1,K), embededFunctions.At(0,2,K)},
                {embededFunctions.At(1,0,K), embededFunctions.At(1,1,K), embededFunctions.At(1,2,K)},
                {embededFunctions.At(2,0,K), embededFunctions.At(2,1,K), embededFunctions.At(2,2,K)}
            };

            return res;
        }

        public double[] GetD()
        {
            double[] res = new double[8]
            {
                embededFunctions.At(0,0,D), embededFunctions.At(1,0,D),
                embededFunctions.At(2,0,D), embededFunctions.At(3,0,D),
                embededFunctions.At(4,0,D), embededFunctions.At(5,0,D),
                embededFunctions.At(6,0,D), embededFunctions.At(7,0,D)
            };

            return res;
        }

        /*** CameraCV Wrapping ***/
        public void DisposeCamera() {
            embededFunctions.DisposeCameraInput(this.camera);
        }
        public bool OpenVideoStream(int id = 0) {
            return  embededFunctions.OpenStream(this.camera, id);
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
            return embededFunctions.CheckBuild(core);
        }

        public void Build(){
            embededFunctions.Build(core);
            area = embededFunctions.GetArea(core);
        }
        
        public IntPtr GetCoreCamera() {
            return this.camera;
        }
        public void SetCoreCamera(IntPtr cam) {
            embededFunctions.setCoreCamera(this.core, cam);
        }
        public void SetCannyThreshold(int thresh)
        {
            embededFunctions.setCannyThreshold(this.core, thresh);
        }
        public void SetCannyThreshold2(int thresh)
        {
            embededFunctions.setCannyThreshold2(this.core, thresh);
        }
        public void SetKernelThreshold1(int thresh)
        {
            embededFunctions.setKernelThreshold1(this.core, thresh);
        }
        public void SetKernelThreshold2(int thresh)
        {
            embededFunctions.setKernelThreshold2(this.core, thresh);
        }

        public void Start() {
            embededFunctions.Start(this.core);
        }

        public void InitTransformDefault()
        {
            tranformTracking = embededFunctions.CreateTransformTracking();
            embededFunctions.InitTransformDefault(tranformTracking, area);
        }
        
        public void InitTransform() {
            tranformTracking = embededFunctions.CreateTransformTracking();
            embededFunctions.InitTransform(tranformTracking, area, K ,D);

        }

        public void InitTransformKD(double[,] K, double[] D)
        {
            tranformTracking = embededFunctions.CreateTransformTracking();
            embededFunctions.InitTransformKD(tranformTracking, area,
                K[0, 0], K[0, 1], K[0, 2],
                K[1, 0], K[1, 1], K[1, 2],
                K[2, 0], K[2, 1], K[2, 2],
                D[0], D[1], D[2], D[3], D[4], D[5], D[6], D[7]);
        }
		
        public void UpdateTranform() {
            embededFunctions.UpdateTransform(tranformTracking, area);
        }

        public void Tracking() {
            embededFunctions.Tracking(core);
            area = embededFunctions.GetArea(core);
        }

        public bool CheckTracking() {
            return embededFunctions.CheckTracking(core);
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
            //Console.WriteLine("Testing Wrapper...");
            //CoreWrapper wrap = CoreWrapper.GetInstance();
            //wrap.InitCamera();
            //wrap.OpenVideoStream(0);
            //byte[] test = wrap.GetCameraFrame();
            //wrap.DisplayCameraStream();
            //Console.ReadKey();

            CoreWrapper wrap = CoreWrapper.GetInstance();
            wrap.InitCore();
            wrap.OpenVideoStream(0);
            //wrap.Start();

            while(!wrap.CheckBuid())
                wrap.Build();

            wrap.InitTransform();
            do {
                wrap.Tracking();
                wrap.UpdateTranform();

                double[] rot = wrap.GetDeltaRot();
                for(int i = 0; i < 3; i++) {
                    Console.Write(rot[i] + " ");
                }
            } while(wrap.CheckTracking());

            Console.ReadKey();
        }
    }
}
