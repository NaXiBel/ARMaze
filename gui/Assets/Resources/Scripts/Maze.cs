using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Maze : MonoBehaviour {

	private Ball ball = null;
	private float epsilon = 1.0f;
	private void RotateMazeTest() {
		Vector3 eulerRotation = this.transform.eulerAngles;

		if(Input.GetKey("left")) {
			this.ball.WakeUp();
			this.transform.Rotate(0.0f, 0.0f, epsilon);
		}

		if(Input.GetKey("right")) {
			this.ball.WakeUp();
			this.transform.Rotate(0.0f, 0.0f, -epsilon);
		}

		if(Input.GetKey("up")) {
			this.ball.WakeUp();
			this.transform.Rotate(epsilon, 0.0f, 0.0f);
		}

		if(Input.GetKey("down")) {
			this.ball.WakeUp();
			this.transform.Rotate(-epsilon, 0.0f, 0.0f);
		}
	}
	// Use this for initialization
	void Start () {
		this.ball = GameObject.Find(Const.BALL_GAMEOBJECT_NAME).GetComponent<Ball>(); 
	}
	
	// Update is called once per frame
	void Update () {
        //public static IntPtr GetDeltaRot(IntPtr transformTracking);
        this.RotateMazeTest();
	}
}
