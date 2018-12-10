using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class StartMenu : MonoBehaviour {

	// Use this for initialization
	void Start () {
        _optionsPanel = GameObject.Find("OptionsPanel").gameObject;
        _creditsPanel = GameObject.Find("CreditsPanel").gameObject;
        _optionsPanel.SetActive(false);
        _creditsPanel.SetActive(false);
	}
	
	// Update is called once per frame
	void Update () {
		
	}

    public string _levelToLoad = "Main";
    public GameObject _optionsPanel;
    public GameObject _creditsPanel;

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
        _optionsPanel.SetActive(true);
    }

    public void CloseOptions() {
        _optionsPanel.SetActive(false);
    }

    public void OpenCredits() {
        _creditsPanel.SetActive(true);
    }

    public void CloseCredits() {
        _creditsPanel.SetActive(false);
    }
}
