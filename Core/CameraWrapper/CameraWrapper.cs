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

        static void Main(string[] args) {
            //Console.WriteLine("Testing VideoStream.dll...");
            //IntPtr test = embededFunctions.CreateCameraInput();
            //embededFunctions.OpenStream(test);
            //embededFunctions.DisplayStream(test);

            Console.WriteLine("Testing Wrapper...");
            CameraWrapper wrap = CameraWrapper.GetInstance();
            wrap.InitCamera();
            wrap.OpenVideoStream(0);
            byte[] test = wrap.GetCameraFrame();
            wrap.DisplayCameraStream();

            Console.ReadKey();
        }
    }
}
