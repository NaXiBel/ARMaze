using System;
using UnityEngine;
using UnityEngine.UI;

public class Chrono : MonoBehaviour {
    float time;

    public Text chrono;

    void Update() {
        this.time = (float)(Math.Truncate((double)Time.timeSinceLevelLoad * 100.0) / 100.0);
        this.time = (float)Math.Round(this.time, 2);
        this.chrono.text = this.time.ToString();
    }
}
