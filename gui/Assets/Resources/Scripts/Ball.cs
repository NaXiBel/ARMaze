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

	/*
	
		La rotation de la balle se fait selon l'axe fixe de l'espace (Space.World), et
		en fonction du déplacement de la balle selon ce même repère.

	 */
	private void UpdateRotation() {
		Vector3 direction = this.oldPosition - this.transform.position;
		float xRotation = 0.0f;
		float zRotation = 0.0f;

		Vector3 ballVelocity = this.GetComponent<Rigidbody>().velocity;

		if(Mathf.Abs(direction.z) < 0.5 ) {
			zRotation = -ballVelocity.x;
		}
		
		if(Mathf.Abs(direction.x) < 0.5) {
			xRotation = ballVelocity.z;
		}

		this.transform.Rotate(new Vector3(xRotation, 0, zRotation) , Space.World);
		
	}

	public void WakeUp() {
		this.sleeping = false;
	}

	void Start () {
		this.oldPosition = this.transform.position;
		this.InitializeBall(); 
	}


	/**
	 */
	void LateUpdate() {
		this.oldPosition = this.transform.position;
	}

	/**
		Physique Unity : lorsqu'une collision est détectée, le rigidbody
		se met en "veille"
	 */
	private void OnCollisionEnter(Collision other) {
		this.sleeping = true;
	}

	/*

	 */
	private void OnCollisionStay(Collision other) {	

		if(other.gameObject.GetComponent<MazeObstacle>()) {
			this.UpdateRotation();
			if(this.sleeping) {
				this.GetComponent<Rigidbody>().WakeUp();
			}

		}
	}
}
