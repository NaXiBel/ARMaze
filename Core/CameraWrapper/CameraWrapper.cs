using System;
using System.Runtime.InteropServices;

namespace Wrapper {

    public class CameraWrapper {
        public struct embededFunctions {
            const string dllpath = @".\VideoStream.dll";
            //const string dllpath = @"D:\ARMaze - Copie\Core\x64\Debug\VideoStream.dll";
            [DllImport(dllpath, EntryPoint = "createCamera")]static public extern IntPtr CreateCameraInput();
            [DllImport(dllpath, EntryPoint = "disposeCamera")]static public extern void DisposeCameraInput(IntPtr pCam);
            [DllImport(dllpath, EntryPoint = "openStream")]static public extern void OpenStream(IntPtr pCam, int id = 0);
            [DllImport(dllpath, EntryPoint = "displayStream")] static public extern void DisplayStream(IntPtr pCam);
            [DllImport(dllpath, EntryPoint = "getLiveFrame")]static public extern IntPtr GetLiveFrame(IntPtr pCam, out int sizeofMat);
            [DllImport(dllpath, EntryPoint = "getWidth")]static public extern int GetWidth(IntPtr pCam);
            [DllImport(dllpath, EntryPoint = "getHeight")]static public extern int GetHeight(IntPtr pCam);

            [DllImport(dllpath, EntryPoint = "create_area")] static public extern IntPtr CreateArea();
            [DllImport(dllpath, EntryPoint = "get_begin_center")] static public extern IntPtr GetBeginCenter(IntPtr area, IntPtr transformTracking);
            [DllImport(dllpath, EntryPoint = "get_end_center")] static public extern IntPtr GetEndCenter(IntPtr area, IntPtr transformTracking);
            [DllImport(dllpath, EntryPoint = "get_wall")] static public extern IntPtr GetWall(IntPtr area, IntPtr transformTracking, int i);
            [DllImport(dllpath, EntryPoint = "get_point")] static public extern IntPtr GetPoint(int j, IntPtr vectorPoint);
            [DllImport(dllpath, EntryPoint = "nb_of_walls")] static public extern int NbOfWalls(IntPtr area);
            [DllImport(dllpath, EntryPoint = "size")] static public extern int Size(IntPtr vectorPoint);
            [DllImport(dllpath, EntryPoint = "get_x")] static public extern int GetX(IntPtr point2d);
            [DllImport(dllpath, EntryPoint = "get_y")] static public extern int GetY(IntPtr point2d);

            [DllImport(dllpath, EntryPoint = "createCore")] static public extern IntPtr CreateCore();
            [DllImport(dllpath, EntryPoint = "video")] static public extern void Video(IntPtr core);
            [DllImport(dllpath, EntryPoint = "check_build")] static public extern bool CheckBuild(IntPtr core);
            [DllImport(dllpath, EntryPoint = "build")] static public extern void Build(IntPtr core);
            [DllImport(dllpath, EntryPoint = "init_transform")] static public extern void InitTransform(IntPtr tranformTracking, IntPtr area);
            [DllImport(dllpath, EntryPoint = "update_transform")] static public extern void UpdateTransform(IntPtr tranformTracking, IntPtr area);
            [DllImport(dllpath, EntryPoint = "tracking")] static public extern IntPtr Tracking(IntPtr core);
            [DllImport(dllpath, EntryPoint = "check_tracking")] static public extern bool CheckTracking(IntPtr core);

            [DllImport(dllpath, EntryPoint = "create_transform_tracking")] static public extern IntPtr CreateTransformTracking();
            [DllImport(dllpath, EntryPoint = "get_init_rot")] static public extern IntPtr GetInitRot(IntPtr transformTracking);
            [DllImport(dllpath, EntryPoint = "get_delta_rot")] static public extern IntPtr GetDeltaRot(IntPtr transformTracking);
            [DllImport(dllpath, EntryPoint = "get_init_trans")] static public extern IntPtr GetInitTrans(IntPtr transformTracking);
            [DllImport(dllpath, EntryPoint = "get_delta_trans")] static public extern IntPtr GetDeltaTrans(IntPtr transformTracking);
            [DllImport(dllpath, EntryPoint = "at")] static public extern double At(int x, int y, IntPtr mat);

        }

        private static CameraWrapper instance = null;
        private IntPtr camera;
        private IntPtr core;
        private IntPtr area;
        private IntPtr tranformTracking;

        private CameraWrapper() {}

        static public CameraWrapper GetInstance() {
            if(instance == null) {
                instance = new CameraWrapper();
            }

            return instance;
        }

        public void InitCamera() {
            this.camera = embededFunctions.CreateCameraInput();
        }

        public void OpenVideoStream(int id = 0) {
            embededFunctions.OpenStream(this.camera, id);
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

        public void DisplayCameraStream() {
            embededFunctions.DisplayStream(this.camera);
        }

        public void DisposeCamera() {
            embededFunctions.DisposeCameraInput(this.camera);
        }

        public void InitCore() {
            this.core = embededFunctions.CreateCore();
        }

        public void Video() {
            embededFunctions.Video(core);
        }

        public bool CheckBuid() {
            return embededFunctions.CheckBuild(core);
        }

        public void Build(){
            embededFunctions.Build(core);
        }

        public void InitTrasform() {
            area = embededFunctions.CreateArea();
            tranformTracking = embededFunctions.CreateTransformTracking();
            embededFunctions.InitTransform(tranformTracking, area);
        }

        public void UpdateTranform() {
            embededFunctions.UpdateTransform(tranformTracking, area);
        }

        public void InitMazeData() {

        }

        public void Tracking() {
            embededFunctions.Tracking(core);
        }

        public bool CheckTracking() {
            return embededFunctions.CheckTracking(core);
        }

        public double[,] GetInitRot() {
            double[,] rot = new double[3, 3];
            IntPtr matRot = embededFunctions.GetInitRot(tranformTracking);
            for(int i = 0 ; i < 3 ; i++) {
                for(int j = 0 ; j < 3 ; j++) {
                    rot[i, j] = embededFunctions.At(i, j, matRot);
                }
            }
            return rot;
        }

        public double[,] GetInitTrans() {
            double[,] trans = new double[3, 3];
            IntPtr matTrans = embededFunctions.GetInitTrans(tranformTracking);
            for (int i = 0 ; i < 3 ; i++) {
                for (int j = 0 ; j < 3 ; j++) {
                    trans[i, j] = embededFunctions.At(i, j, matTrans);
                }
            }
            return trans;
        }

        public double[,] GetDeltaRot() {
            double[,] rot = new double[3, 3];
            IntPtr matRot = embededFunctions.GetDeltaRot(tranformTracking);
            for (int i = 0 ; i < 3 ; i++) {
                for (int j = 0 ; j < 3 ; j++) {
                    rot[i, j] = embededFunctions.At(i, j, matRot);
                }
            }
            return rot;
        }

        public double[,] GetDeltaTrans() {
            double[,] trans = new double[3, 3];
            IntPtr matTrans = embededFunctions.GetDeltaTrans(tranformTracking);
            for (int i = 0 ; i < 3 ; i++) {
                for (int j = 0 ; j < 3 ; j++) {
                    trans[i, j] = embededFunctions.At(i, j, matTrans);
                }
            }
            return trans;
        }

        static void Main(string[] args) {
            //Console.WriteLine("Testing VideoStream.dll...");
            //IntPtr test = embededFunctions.CreateCameraInput();
            //embededFunctions.OpenStream(test);
            //embededFunctions.DisplayStream(test);

            /*
            Console.WriteLine("Testing Wrapper...");
            CameraWrapper wrap = CameraWrapper.GetInstance();
            wrap.InitCamera();
            wrap.OpenVideoStream(0);
            byte[] test = wrap.GetCameraFrame();
            wrap.DisplayCameraStream();
            */

            CameraWrapper wrap = CameraWrapper.GetInstance();
            wrap.InitCore();
            wrap.Video();

            while (wrap.CheckBuid())
                wrap.Build();
            wrap.InitTrasform();
            do {
                wrap.Tracking();
                wrap.UpdateTranform();

                double[,] rot = wrap.GetDeltaRot();
                for(int i = 0 ; i < 3 ; i++) {
                    for(int j = 0 ; j < 3 ; j++) {
                        Console.Write(rot[i, j] + " ");
                    }
                    Console.WriteLine();
                }

            } while (wrap.CheckTracking());

            Console.ReadKey();
        }

    }
}
