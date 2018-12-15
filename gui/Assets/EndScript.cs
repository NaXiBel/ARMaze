using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EndScript : MonoBehaviour {

    private void OnTriggerEnter(Collider other)
    {
        if(other.gameObject.tag.Equals("Ball"))
        {
            GameObject.Find("InGame").GetComponent<InGameController>().Win();
            GameObject.Find("VideoStream").GetComponent<CameraRenderer>().Pause();
            //GameObject.FindGameObjectWithTag("Maze").SetActive(false);
        }
    }

}
