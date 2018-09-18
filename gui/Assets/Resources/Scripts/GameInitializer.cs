using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GameInitializer : MonoBehaviour {

	private Vector3 GetMazeScale() {
		Vector3 mazeScale = new Vector3(10.0f, 10.0f, 1.0f);
		
		return mazeScale;
	}

	private void initializeMaze() {

		GameObject prefab = ((GameObject)Resources.Load("Prefabs/" + Const.OBSTACLE_PREFAB_NAME, typeof(GameObject)));
		Renderer rend = prefab.GetComponent<Renderer>();
		Vector3 mazeScale = this.GetMazeScale();
		prefab.transform.localScale = mazeScale;
		
		rend.sharedMaterial.SetTextureScale("_MainTex", new Vector2(mazeScale.x, mazeScale.y));

		GameObject o = Instantiate(prefab, Vector3.zero, Quaternion.Euler(90.0f, 0.0f, 0.0f) );
		o.transform.parent = GameObject.Find(Const.MAZE_GAMEOBJECT_NAME).transform;
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
