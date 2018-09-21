using System;
using UnityEngine;
using Wrapper;

public class CameraRenderer : MonoBehaviour {
    private byte[] frame;
    private CameraWrapper camera;
    private Texture2D texture;

	// Use this for initialization
	void Start() {
        this.texture = new Texture2D(10, 10, TextureFormat.BGRA32, false);
        this.camera = CameraWrapper.GetInstance();
        Debug.Log("Testing VideoStream.dll + wrapper...");
        this.camera.InitCamera();
        this.camera.OpenVideoStream(1);
        // this.camera.DisplayCameraStream();
    }
	
	// Update is called once per frame
	void Update() {
        this.frame = this.camera.GetCameraFrame();
        this.texture.LoadRawTextureData(this.frame);
        this.texture.Apply();
        this.GetComponent<Renderer>().material.SetTexture("_MainTex", this.texture);
    }
}
