using System;
using UnityEngine;
using Wrapper;

public class CameraRenderer : MonoBehaviour {
    private CameraWrapper camera;

	// Use this for initialization
	void Start () {
        this.camera = CameraWrapper.GetInstance();
        Debug.Log("Testing VideoStream.dll + wrapper...");
        this.camera.InitCamera();
        this.camera.OpenVideoStream(1);
        this.camera.DisplayCameraStream();
    }
	
	// Update is called once per frame
	void Update () {
		
	}
}
