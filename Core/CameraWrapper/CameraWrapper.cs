using System;
using System.Runtime.InteropServices;

namespace Wrapper {
    public class CameraWrapper {
        public struct embededFunctions {
            const string dllpath = "./VideoStream.dll";
            //const string dllpath = @"C:\Users\alexm\Documents\ARMaze\Core\x64\Debug\VideoStream.dll";
            [DllImport(dllpath, EntryPoint = "createCamera")]static public extern IntPtr CreateCameraInput();
            [DllImport(dllpath, EntryPoint = "disposeCamera")]static public extern void DisposeCameraInput(IntPtr pCam);
            [DllImport(dllpath, EntryPoint = "openStream")]static public extern void OpenStream(IntPtr pCam, int id);
            [DllImport(dllpath, EntryPoint = "displayStream")] static public extern void DisplayStream(IntPtr pCam);
            [DllImport(dllpath, EntryPoint = "getLiveFrame")]static public extern byte GetLiveFrame(IntPtr pCam);
            [DllImport(dllpath, EntryPoint = "getWidth")]static public extern int GetWidth(IntPtr pCam);
            [DllImport(dllpath, EntryPoint = "getHeight")]static public extern int GetHeight(IntPtr pCam);
        }

        private static CameraWrapper instance = null;
        private IntPtr camera;

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

        public byte GetCameraFrame() {
            return embededFunctions.GetLiveFrame(this.camera);
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

        //static void Main(string[] args) {
        //    Console.WriteLine("Testing VideoStream.dll...");
        //    IntPtr test = embededFunctions.CreateCameraInput();
        //    embededFunctions.OpenStream(test);
        //    embededFunctions.DisplayStream(test);

        //    Console.WriteLine("Testing Wrapper...");
        //    CameraWrapper wrap = CameraWrapper.GetInstance();
        //    wrap.InitCamera();
        //    wrap.OpenVideoStream();
        //    wrap.DisplayCameraStream();

        //    Console.ReadKey();
        //}
    }
}
