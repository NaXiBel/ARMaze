using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EndScript : MonoBehaviour {

    private void OnTriggerEnter(Collider other)
    {
        if(other.gameObject.name.Equals("Ball"))
        {
            GameObject.Find("InGame").GetComponent<InGameController>().Win();
        }
    }

}
