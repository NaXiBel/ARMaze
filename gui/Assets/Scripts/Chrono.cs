using System;
using UnityEngine;
using UnityEngine.UI;

public class Chrono : MonoBehaviour {
    bool stopped;
    float startTime;
    float ellapsedTime;

    public Text chrono;

    public void StartChrono() {
        this.stopped = false;
    }

    public void StopChrono() {
        this.stopped = true;
    }

    public void ResetChrono() {
        this.ellapsedTime = 0;
        this.chrono.text = this.ellapsedTime.ToString();
    }

    void Start() {
        StopChrono();
        ResetChrono();
        StartChrono();
    }

    void Update() {
        if(!this.stopped) {
            this.ellapsedTime = (float)(Math.Truncate((double)Time.time * 100.0) / 100.0);
            this.ellapsedTime = (float)Math.Round(this.ellapsedTime, 2);
            this.chrono.text = this.ellapsedTime.ToString();
        }
    }
}
