using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PauseScript : MonoBehaviour {

    public InGameController inGameController;

    public void Pause()
    {
        inGameController.Pause();
    }

}
