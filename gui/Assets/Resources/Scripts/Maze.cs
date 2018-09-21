using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Maze : MonoBehaviour {

	private Ball ball = null;
	private void RotateMazeTest() {
		Vector3 eulerRotation = this.transform.eulerAngles;

		if(Input.GetKey("left")) {
			this.ball.WakeUp();
			this.transform.Rotate(eulerRotation.x, eulerRotation.y, eulerRotation.z + 5.0f);
		}

		if(Input.GetKey("right")) {
			this.ball.WakeUp();
			this.transform.Rotate(eulerRotation.x, eulerRotation.y, eulerRotation.z - 5.0f);
		}

		if(Input.GetKey("up")) {
			this.ball.WakeUp();
			this.transform.Rotate(eulerRotation.x + 5.0f, eulerRotation.y, eulerRotation.z);
		}

		if(Input.GetKey("down")) {
			this.ball.WakeUp();
			this.transform.Rotate(eulerRotation.x - 5.0f, eulerRotation.y, eulerRotation.z);
		}
	}
	// Use this for initialization
	void Start () {
		this.ball = GameObject.Find(Const.BALL_GAMEOBJECT_NAME).GetComponent<Ball>(); 
	}
	
	// Update is called once per frame
	void Update () {
		this.RotateMazeTest();
	}
}
