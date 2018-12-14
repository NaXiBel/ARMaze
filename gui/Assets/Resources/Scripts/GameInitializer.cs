using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Wrapper;
public class GameInitializer : MonoBehaviour {

	private Vector3 GetMazeScale() {
		Vector3 mazeScale = new Vector3(10.0f, 10.0f, 1.0f);
		return mazeScale;
	}

    private void initializeMaze() {

        Debug.Log("Initgo");

    
        GameObject prefabObstacle = ((GameObject)Resources.Load("Prefabs/" + Const.OBSTACLE_PREFAB_NAME, typeof(GameObject)));

        GameObject o = Instantiate(prefabObstacle, Vector3.zero, Quaternion.Euler(90.0f, 0.0f, 0.0f));
        Vector3 mazeScale = this.GetMazeScale();
        o.transform.localScale = mazeScale;
        o.transform.parent = GameObject.Find(Const.MAZE_GAMEOBJECT_NAME).transform;
        Renderer rend = o.GetComponent<Renderer>();
        rend.material.SetTextureScale("_MainTex", new Vector2(mazeScale.x, mazeScale.y));


        GameObject arrivalPrefab = ((GameObject)Resources.Load("Prefabs/" + Const.POINT_OF_ARRIVAL_PREFAB_NAME, typeof(GameObject)));
        double[] end = CoreWrapper.GetInstance().GetEndCenter();
        //GameObject arrivalObject = Instantiate(arrivalPrefab, MazeData.MAZE_POINT_OF_ARRIVAL, Quaternion.Euler(-90.0f, 0.0f, 0.0f));
        float x_scale_arrivee = -Const.HAUTEUR_MAZE / 2f + Const.HAUTEUR_MAZE * (float)end[0];
        float y_scale_arrivee = -Const.LARGEUR_MAZE / 2f + Const.LARGEUR_MAZE * (float)end[1];
        GameObject arrivalObject = Instantiate(arrivalPrefab, new Vector3(x_scale_arrivee, 0f, y_scale_arrivee), Quaternion.Euler(-90.0f, 0.0f, 0.0f));
        arrivalObject.transform.parent = GameObject.Find(Const.MAZE_GAMEOBJECT_NAME).transform;
        arrivalObject.transform.localScale = new Vector3(0.25f, 0.25f, 0.25f);

        ParticleSystem arrivalPs = arrivalObject.GetComponent<ParticleSystem>();
        ParticleSystem.MainModule arrivalMain = arrivalPs.main;

        arrivalPs.transform.localScale = new Vector3(0.25f, 0.25f, 0.25f);
        ParticleSystemRenderer arrivalPsr = arrivalObject.GetComponent<ParticleSystemRenderer>();
        arrivalPsr.renderMode = ParticleSystemRenderMode.Billboard;
        Debug.Log(arrivalMain.simulationSpace);
        arrivalMain.simulationSpace = ParticleSystemSimulationSpace.Local;


        /* for (int i = 0; i < MazeData.ARRAY_DATAS_TEST.Length / 2; ++i)
         {
             MazeObstacle.Create(MazeData.ARRAY_DATAS_TEST[i, 0], MazeData.ARRAY_DATAS_TEST[i, 1]);
         }*/
        List<double[,]> walls = CoreWrapper.GetInstance().GetWall();
        foreach(double[,] wall in walls)
        {
           // Debug.Log("(" + -10f / 2f + 10f * (float)wall[0, 0] + " , " + -10f / 2f + 10f * (float)wall[0, 1] + "); (" + -10f / 2f + 10f * (float)wall[1, 0] + " , " + -10f / 2f + 10f * (float)wall[1, 1] + ")");
           
            float x_scale_wall_start = -Const.HAUTEUR_MAZE / 2f + Const.HAUTEUR_MAZE * (float)wall[0, 0];
            float y_scale_wall_start = -Const.LARGEUR_MAZE / 2f + Const.LARGEUR_MAZE * (float)wall[0, 1];
            float x_scale_wall_end = -Const.HAUTEUR_MAZE / 2f + Const.HAUTEUR_MAZE * (float)wall[1, 0];
            float y_scale_wall_end = -Const.LARGEUR_MAZE / 2f + Const.LARGEUR_MAZE * (float)wall[1, 1];
            Debug.Log("(" + x_scale_wall_start + " , " + y_scale_wall_start + "); (" + x_scale_wall_end + " , " + y_scale_wall_end + ")");

            MazeObstacle.Create(new Vector3 (x_scale_wall_start, 1f, y_scale_wall_start), new Vector3(x_scale_wall_end, 1f, y_scale_wall_end));
        }

        GameObject.Find(Const.MAZE_GAMEOBJECT_NAME).transform.position = new Vector3(3.0f, 368.0f, -5.0f);
        
    }

    void Awake() {
		this.initializeMaze();
	}
	
	// Use this for initialization
	void Start () {
    }
	
	// Update is called once per frame
	void Update () {
     //   this.initializeMaze();
    }
}
