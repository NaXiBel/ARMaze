using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GameInitializer : MonoBehaviour {

	private Vector3 GetMazeScale() {
		Vector3 mazeScale = new Vector3(10.0f, 10.0f, 1.0f);
		return mazeScale;
	}

	private void initializeMaze() {

		GameObject prefabObstacle = ((GameObject)Resources.Load("Prefabs/" + Const.OBSTACLE_PREFAB_NAME, typeof(GameObject)));

		GameObject o = Instantiate(prefabObstacle, Vector3.zero, Quaternion.Euler(90.0f, 0.0f, 0.0f) );
		Vector3 mazeScale = this.GetMazeScale();
		o.transform.localScale = mazeScale;
		o.transform.parent = GameObject.Find(Const.MAZE_GAMEOBJECT_NAME).transform;
		Renderer rend = o.GetComponent<Renderer>();
		rend.material.SetTextureScale("_MainTex", new Vector2(mazeScale.x, mazeScale.y));
		
		GameObject arrivalPrefab = ((GameObject)Resources.Load("Prefabs/" + Const.POINT_OF_ARRIVAL_PREFAB_NAME, typeof(GameObject)));
		GameObject arrivalObject = Instantiate(arrivalPrefab, MazeData.MAZE_POINT_OF_ARRIVAL, Quaternion.Euler(-90.0f, 0.0f, 0.0f));
		arrivalObject.transform.parent = GameObject.Find(Const.MAZE_GAMEOBJECT_NAME).transform;
		arrivalObject.transform.localScale = new Vector3(0.25f, 0.25f, 0.25f);

		ParticleSystem arrivalPs = arrivalObject.GetComponent<ParticleSystem>();
		ParticleSystem.MainModule arrivalMain = arrivalPs.main;

		arrivalPs.transform.localScale = new Vector3(0.25f, 0.25f, 0.25f);
		ParticleSystemRenderer arrivalPsr = arrivalObject.GetComponent<ParticleSystemRenderer>(); 
		arrivalPsr.renderMode = ParticleSystemRenderMode.Billboard;
		Debug.Log(arrivalMain.simulationSpace);
		arrivalMain.simulationSpace = ParticleSystemSimulationSpace.Local;
		

		for(int i = 0; i < MazeData.ARRAY_DATAS_TEST.Length/2; ++i) {
			MazeObstacle.Create(MazeData.ARRAY_DATAS_TEST[i, 0], MazeData.ARRAY_DATAS_TEST[i, 1]);
		}
	}

	void Awake() {
		this.initializeMaze();
	}
	
	// Use this for initialization
	void Start () {
		
	}
	
	// Update is called once per frame
	void Update () {
		
	}
}
