using System;
using UnityEngine;
using Wrapper;

public class CameraRenderer : MonoBehaviour {
    private byte[] frame;
    // private CameraWrapper camera;
    private CameraWrapper camera;
    private Texture2D texture = null;
    private string m_MazeNomPrefab;
    private bool m_FinishedBuild;
    private GameObject maze;
    // Use this for initialization
    void Start() {
        camera = CameraWrapper.GetInstance();
        camera.InitCore();
        camera.OpenVideoStream(0);
        this.frame = camera.GetCameraFrame();
        this.texture = new Texture2D(camera.GetFrameWidth(), camera.GetFrameHeight(), TextureFormat.BGRA32, false);
        this.transform.localScale = new Vector3(camera.GetFrameWidth(), camera.GetFrameHeight(), 1);

        //  Camera.main.transform.position = this.transform.position;
        //  Camera.main.transform.Translate(Vector3.back);
        Camera.main.orthographicSize = camera.GetFrameHeight() / 2f + 2;
        m_FinishedBuild = false;
        
    }

    // Update is called once per frame
    void Update() {

        //this.camera.Video();
        if(!m_FinishedBuild) {
            this.frame = camera.GetCameraFrame();

            camera.Build();

            if(camera.CheckBuid()) {
                m_FinishedBuild = true;
                camera.InitTransform();
                Debug.Log("Built");
                double[] start = CameraWrapper.GetInstance().GetBeginCenter();
                GameObject prefabBall = ((GameObject)Resources.Load("Prefabs/" + Const.BALL_PREFAB_NAME, typeof(GameObject)));
                float x_unity = -Const.HAUTEUR_MAZE / 2 + Const.HAUTEUR_MAZE * (float)start[0];
                float y_unity = -Const.LARGEUR_MAZE / 2 + Const.LARGEUR_MAZE * (float)start[1];

                GameObject objetBall = Instantiate(prefabBall, new Vector3(x_unity, 5f, y_unity), Quaternion.Euler(90.0f, 0.0f, 0.0f));


                GameObject o = ((GameObject)Resources.Load("Prefabs/" + Const.MAZE_PREFAB_NAME, typeof(GameObject)));
                maze = Instantiate(o, Vector3.zero, Quaternion.Euler(0.0f, 0.0f, 0.0f));

                GameObject Init = ((GameObject)Resources.Load("Prefabs/" + Const.GAMEINITIALIZER_PREFAB_NAME, typeof(GameObject)));
                GameObject o2 = Instantiate(Init, Vector3.zero, Quaternion.Euler(0.0f, 0.0f, 0.0f));

                double[] rot = camera.GetInitRot();
                maze.transform.rotation = Quaternion.Euler((float)rot[0] * 180 / Mathf.PI, (float)rot[2] * 180 / Mathf.PI, (float)rot[1] * 180 / Mathf.PI);

            }
        } else {
            //            do {
            this.frame = camera.GetCameraFrame();

            camera.Tracking();
            camera.UpdateTranform();

            double[] rot = camera.GetDeltaRot();
            /*          double[] end = camera.GetEndCenter();
                        Debug.Log(end[0] + " " + end[1]);
                        */
            Debug.Log(rot[0] + " " + rot[2] + " " + rot[1] + " ");
            maze.transform.Rotate((float)rot[0] * 180 / Mathf.PI, (float)rot[2] * 180 / Mathf.PI, (float)rot[1] * 180 / Mathf.PI);

        }
        this.texture.LoadRawTextureData(this.frame);
        this.texture.Apply();
        this.GetComponent<Renderer>().material.SetTexture("_MainTex", this.texture);
    }
}
