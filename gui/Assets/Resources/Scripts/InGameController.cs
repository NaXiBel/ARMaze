using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class InGameController : MonoBehaviour {
    public string _levelToLoad = "ARMaze";
    private GameObject _gameOverPanel;
    private GameObject _winPanel;
    private GameObject _calibrationPanel;
    private GameObject _pausePanel;
    private GameObject _inGamePanel;
    private Text _inGameScore;
    private Text _pauseScore;
    private float _startTime;
    private float _time;
    private bool _isPaused;

    // Use this for initialization
    void Start () {
        _gameOverPanel = GameObject.Find("GameOver").gameObject;
        _winPanel = GameObject.Find("Win").gameObject;
        _calibrationPanel = GameObject.Find("Calibration").gameObject;
        _pausePanel = GameObject.Find("Pause").gameObject;
        _pauseScore = _pausePanel.transform.Find("Score").GetComponent<Text>();
        _inGamePanel = GameObject.Find("inGame").gameObject;
        _inGameScore = _inGamePanel.transform.Find("Score").GetComponent<Text>();
        _gameOverPanel.SetActive(false);
        _winPanel.SetActive(false);
        _calibrationPanel.SetActive(false);
        _pausePanel.SetActive(false);
        _inGamePanel.SetActive(true);
        this._startTime = 0f;
        this._time = 0f;
        this._isPaused = false;

    }
	
	// Update is called once per frame
	void Update () {
        if (!this._isPaused) {
            this._time += (float)Math.Round((double)Time.deltaTime,2);
            //this._time = (float)(Math.Truncate((double)Time.timeSinceLevelLoad * 100.0) / 100.0);
            //this._time = (float)Math.Round(this._time, 2);
            this._inGameScore.text = this._time.ToString() ;
        }
    }

    public void OpenPause() {
        this._isPaused = true;
        _inGamePanel.SetActive(false);
        _pausePanel.SetActive(true);
        this._pauseScore.text = this._time.ToString();
    }

    public void ClosePause() {
        _inGamePanel.SetActive(true);
        _pausePanel.SetActive(false);
        this._isPaused = false;
    }
}
