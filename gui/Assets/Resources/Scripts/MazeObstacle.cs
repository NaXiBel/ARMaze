using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MazeObstacle : MonoBehaviour {

	private static Vector3 GetObstacleScale(Vector3 p1, Vector3 p2) {

		float scaleX = Mathf.Abs(p1.x - p2.x);
		float scaleY = Mathf.Abs(p1.y - p2.y);
		float scaleZ = Mathf.Abs(p1.z - p2.z);
		
		return new Vector3(scaleX, scaleY, scaleZ);
	}

	public static GameObject Create(Vector3 p1, Vector3 p2) {
		
		
		GameObject prefab = ((GameObject)Resources.Load("Prefabs/" + Const.OBSTACLE_PREFAB_NAME, typeof(GameObject)));
		Renderer rend = prefab.GetComponent<Renderer>();
		Vector3 obstacleScale = MazeObstacle.GetObstacleScale(p1, p2);
		prefab.transform.localScale = obstacleScale;
		
		rend.sharedMaterial.SetTextureScale("_MainTex", new Vector2(obstacleScale.x, obstacleScale.y));

		GameObject o = Instantiate(prefab, Vector3.zero, Quaternion.Euler(0.0f, 0.0f, 0.0f) );
		o.transform.parent = GameObject.Find(Const.MAZE_GAMEOBJECT_NAME).transform;

		return o; 

	}

	void Update () {
		
	}


}
