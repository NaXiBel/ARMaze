using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class StartMenu : MonoBehaviour {

	// Use this for initialization
	void Start () {
        _optionsPanel = GameObject.Find("OptionsPanel").gameObject;
        _creditsPanel = GameObject.Find("CreditsPanel").gameObject;
        _mainPanel = GameObject.Find("MainPanel").gameObject;
        _optionsPanel.SetActive(false);
        _creditsPanel.SetActive(false);
        _mainPanel.SetActive(true);
	}

	// Update is called once per frame
	void Update () {

	}

    public string _levelToLoad = "Main";
    public GameObject _optionsPanel;
    public GameObject _creditsPanel;
    public GameObject _mainPanel;

    public void StartGame()
    {
        Debug.Log("Start");
        SceneManager.LoadScene(_levelToLoad);
    }

    public void QuitGame()
    {
        Debug.Log("Quit");
        Application.Quit();
    }

    public void OpenOptions() {
        _mainPanel.SetActive(false);
        _optionsPanel.SetActive(true);
    }

    public void CloseOptions() {
        _optionsPanel.SetActive(false);
        _mainPanel.SetActive(true);
    }

    public void OpenCredits() {
        _mainPanel.SetActive(false);
        _creditsPanel.SetActive(true);
    }

    public void CloseCredits() {
        _creditsPanel.SetActive(false);
        _mainPanel.SetActive(true);
    }
}
