using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MazeObstacle : MonoBehaviour {

	private static Vector3 GetObstacleScale(Vector3 p1, Vector3 p2) {

		float scaleX = Mathf.Sqrt((p2.x - p1.x)*(p2.x - p1.x) + (p2.z - p1.z)*(p2.z - p1.z));
		
		return new Vector3(scaleX, 2.0f, 0.1f);
	}

	private static Vector3 GetMiddleBetweenPoints(Vector3 p1, Vector3 p2) {
		float middleX = (p1.x + p2.x) / 2.0f;
		float middleY = (p1.y + p2.y) / 2.0f;
		float middleZ = (p1.z + p2.z) / 2.0f;

		return new Vector3(middleX, 1.0f, middleZ);
	}

	private static Vector3 GetWallOrientation(Vector3 p1, Vector3 p2) {

		float slope;
		if((p2.z - p1.z) != 0.0f && (p2.x - p1.x) != 0.0f) {
			slope = (p2.z - p1.z) / (p2.x - p1.x);
		} else {
			if((p2.z - p1.z) == 0.0f) {
				slope = 0.0f;
			} else if ((p2.x - p1.x) == 0.0f) {
				slope = 2.0f;
			} else {
				slope = 0.0f;
			}
		}

		return new Vector3(0.0f, slope * -45.0f, 0.0f);

	}

	public static GameObject Create(Vector3 p1, Vector3 p2) {
		
		GameObject prefab = ((GameObject)Resources.Load("Prefabs/" + Const.OBSTACLE_PREFAB_NAME, typeof(GameObject)));
		Vector3 obstacleScale = MazeObstacle.GetObstacleScale(p1, p2);

		Vector3 spawn = GetMiddleBetweenPoints(p1, p2);

		GameObject o = Instantiate(prefab, spawn, Quaternion.Euler(0.0f, 0.0f, 0.0f) );

		Renderer rend = o.GetComponent<Renderer>();
		o.transform.parent = GameObject.Find(Const.MAZE_GAMEOBJECT_NAME).transform;
		o.transform.localScale = obstacleScale;
		o.transform.Rotate(GetWallOrientation(p1, p2));
		
		rend.material.SetTextureScale("_MainTex", new Vector2(obstacleScale.x, obstacleScale.y));
		return o; 

	}

	void Update () {
		
	}


}
