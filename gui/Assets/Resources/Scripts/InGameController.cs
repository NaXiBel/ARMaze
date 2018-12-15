using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

public class InGameController : MonoBehaviour {

    enum State
    {
        INIT, // searching the maze
        RUNNING, // maze found, timer starts
        PAUSED, // game paused
        FINISHED // game finished
    }

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
    private State _state;

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
        this._state = State.INIT;
        _inGameScore.text = "Initializing the maze";
    }
	
	// Update is called once per frame
	void Update () {
        if (_state == State.RUNNING) {
            this._time += (float)Math.Round((double)Time.deltaTime,2);
            //this._time = (float)(Math.Truncate((double)Time.timeSinceLevelLoad * 100.0) / 100.0);
            //this._time = (float)Math.Round(this._time, 2);
            this._inGameScore.text = this._time.ToString() ;
        }
    }

    public void StartTimer()
    {
        _state = State.RUNNING;
    }

    public void Win()
    {
        _state = State.FINISHED;
        _winPanel.SetActive(true);
        _inGamePanel.SetActive(false);
    }

    public void Loose()
    {
        _state = State.FINISHED;
        _gameOverPanel.SetActive(true);
        _inGamePanel.SetActive(false);
    }

    public void Pause() {
        
        if(_state != State.INIT)
            this._state = State.PAUSED;
        _inGamePanel.SetActive(false);
        _pausePanel.SetActive(true);
        this._pauseScore.text = this._time.ToString();
    }

    public void Resume() {
        _inGamePanel.SetActive(true);
        _pausePanel.SetActive(false);
        if(_state != State.INIT)
            this._state = State.RUNNING;
    }

    public void GoToMenu()
    {
        SceneManager.LoadScene("ARMaze");
    }

    public void Restart()
    {
        SceneManager.LoadScene("InGame");
    }

    public void Quit()
    {
        Application.Quit();
    }
    
}
