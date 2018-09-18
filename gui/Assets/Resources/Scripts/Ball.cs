using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Ball : MonoBehaviour {
	private int i = 0;
	private bool sleeping;
	private Vector3 oldPosition;
	private void InitializeBall() {
		this.sleeping = false;

	}

	private void UpdateRotation() {
		Vector3 direction = this.transform.position - this.oldPosition;
		Vector3 eulerRotation = this.transform.rotation.eulerAngles;

		this.transform.rotation = Quaternion.Euler(eulerRotation.x + direction.x*50, eulerRotation.y + direction.y*50, eulerRotation.z + direction.z*50);

	}

	public void WakeUp() {
		this.sleeping = false;
	}

	void Start () {
		this.oldPosition = this.transform.position;
		this.InitializeBall(); 
	}

	
	void Update () {

	}

	void LateUpdate() {
		this.oldPosition = this.transform.position;
	}

	private void OnCollisionEnter(Collision other) {
		this.sleeping = true;
	}

	/*

	 */
	private void OnCollisionStay(Collision other) {	

		if(other.gameObject.GetComponent<MazeObstacle>()) {
			this.UpdateRotation();
			if(this.sleeping) {
				Debug.Log("Awake !");
				this.GetComponent<Rigidbody>().WakeUp();
			}

		}
	}
}
