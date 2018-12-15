using System;
using System.Collections;
using UnityEngine;
using UnityEditor;
using Wrapper;
using System.Xml;
using System.Xml.Serialization;
using System.IO;

public class CameraRenderer : MonoBehaviour {

    private bool cameraOk;
    private byte[] frame;
    private CoreWrapper core;
    private Texture2D texture = null;
    private string m_MazeNomPrefab;
    private bool m_FinishedBuild;
    private GameObject maze;
    private bool m_calibrated;
    private bool m_config_exists;
    private Xml2CSharp.Opencv_storage config;

    public float rotOffsetX;
    public float rotOffsetY;
    public float rotOffsetZ;

    private Vector3 rotLab;

    private double accTime;
    private bool showPopUp = false;
    public InGameController inGameController;

    private bool paused = false;

    // Use this for initialization
    void Start() {

        core = CoreWrapper.GetInstance();
        core.InitCore();
        cameraOk = core.OpenVideoStream(0);

        if(!cameraOk)
        {
            showPopUp = true;
            return;
        }

        this.frame = core.GetCameraFrame();
        this.texture = new Texture2D(core.GetFrameWidth(), core.GetFrameHeight(), TextureFormat.BGRA32, false);
        this.transform.localScale = new Vector3(core.GetFrameWidth(), core.GetFrameHeight(), 1);

        //  Camera.main.transform.position = this.transform.position;
        //  Camera.main.transform.Translate(Vector3.back);
        Camera.main.orthographicSize = core.GetFrameHeight() / 2f + 2;
        m_FinishedBuild = false;
        
    }

    private void OnGUI()
    {
        if(showPopUp)
            GUI.Window(0, new Rect((Screen.width / 2) - 150, (Screen.height / 2) - 75
            , 300, 250), ShowGUI, "Error");
    }

    void ShowGUI(int windowID)
    {
        // You may put a label to show a message to the player

        GUI.Label(new Rect(65, 40, 200, 30), "Cannot open the camera stream");

        // You may put a button to close the pop up too

        if(GUI.Button(new Rect(50, 150, 75, 30), "OK"))
        {
            showPopUp = false;
            // you may put other code to run according to your game too
        }

    }

    // Update is called once per frame
    void Update() {

        if(paused)
            return;

        if(!cameraOk)
            return;

        this.frame = core.GetCameraFrame();
        this.texture.LoadRawTextureData(this.frame);
        this.texture.Apply();
        this.GetComponent<Renderer>().material.SetTexture("_MainTex", this.texture);

        /*

        if(!m_calibrated && !m_config_exists)
        {
            
            accTime += Time.deltaTime;
            if( accTime >= 1)
            {
                accTime -= 1;
                Debug.Log("mdr");
                StartCoroutine(AsycnFindPattern());
                //core.AddPatternToCalibrator();
                
                if(core.CheckCalibrator())
                {
                    m_calibrated = true;
                    core.Calibrate();
                }

            }
            return;

        }

        */

        //this.camera.Video();
        if(!m_FinishedBuild) {

            core.Build();

            if (core.CheckBuid())
            {
                m_FinishedBuild = true;

                core.InitTransformDefault();
                
                Debug.Log("Built");
                double[] start = CoreWrapper.GetInstance().GetBeginCenter();
                GameObject prefabBall = ((GameObject)Resources.Load("Prefabs/" + Const.BALL_PREFAB_NAME, typeof(GameObject)));
                float x_unity = -Const.HAUTEUR_MAZE / 2 + Const.HAUTEUR_MAZE * (float)start[0];
                float y_unity = -Const.LARGEUR_MAZE / 2 + Const.LARGEUR_MAZE * (float)start[1];

                GameObject objetBall = Instantiate(prefabBall, new Vector3(x_unity, 5f, y_unity), Quaternion.Euler(90.0f, 0.0f, 0.0f));
                
                GameObject o = ((GameObject)Resources.Load("Prefabs/" + Const.MAZE_PREFAB_NAME, typeof(GameObject)));
                maze = Instantiate(o, Vector3.zero, Quaternion.Euler(0.0f, 0.0f, 0.0f));

                GameObject Init = ((GameObject)Resources.Load("Prefabs/" + Const.GAMEINITIALIZER_PREFAB_NAME, typeof(GameObject)));
                GameObject o2 = Instantiate(Init, Vector3.zero, Quaternion.Euler(0.0f, 0.0f, 0.0f));
                
                double[] rot = core.GetInitRot();

                rotLab = new Vector3(-(float)(rot[0]) + rotOffsetX,
                    -(float)(rot[2]) + rotOffsetY,
                    -(float)(rot[1]) + rotOffsetZ);

                inGameController.StartTimer();

            }
        } else {

            core.Tracking();
            core.UpdateTranform();
            
            double[] rot = core.GetDeltaRot();
            rotLab += new Vector3(-(float)rot[0], -(float)(rot[2]), -(float)(rot[1]));
            
            maze.transform.rotation = Quaternion.Euler(rotLab);

        }
    }

    public void Pause()
    {
        paused = true;
    }

    public void UnPause()
    {
        paused = false;
    }

}
