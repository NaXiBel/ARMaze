using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class SettingsContainer : MonoBehaviour {

    public Scrollbar _canny1Bar;
    public Text _canny1Value;
    public Text _canny1MinValue;
    public Text _canny1MaxValue;
    private float canny1Value;
    private List<TrackbarListener> canny1Listeners = new List<TrackbarListener>();

    public Scrollbar _canny2Bar;
    public Text _canny2Value;
    public Text _canny2MinValue;
    public Text _canny2MaxValue;
    private float canny2Value;
    private List<TrackbarListener> canny2Listeners = new List<TrackbarListener>();

    public Scrollbar _threshold1Bar;
    public Text _threshold1Value;
    public Text _threshold1MinValue;
    public Text _threshold1MaxValue;
    private float threshold1Value;
    private List<TrackbarListener> threshold1Listeners = new List<TrackbarListener>();

    public Scrollbar _threshold2Bar;
    public Text _threshold2Value;
    public Text _threshold2MinValue;
    public Text _threshold2MaxValue;
    private float threshold2Value;
    private List<TrackbarListener> threshold2Listeners = new List<TrackbarListener>();

    void Start() {
        _canny1Bar.onValueChanged.AddListener(Canny1Changed);
        _canny2Bar.onValueChanged.AddListener(Canny2Changed);
        _threshold1Bar.onValueChanged.AddListener(Threshold1Changed);
        _threshold2Bar.onValueChanged.AddListener(Threshold2Changed);
    }

    void Update() {

    }

    private void Canny1Changed(float canny1Bar) {
        canny1Value = int.Parse(_canny1MinValue.text) + canny1Bar * (int.Parse(_canny1MaxValue.text) - int.Parse(_canny1MinValue.text));
        _canny1Value.text = canny1Value.ToString();
        if (canny1Listeners.Count > 0) {
            foreach (TrackbarListener l in canny1Listeners) {
                l.Callback(canny1Value);
            }
        }
    }

    private void Canny2Changed(float canny2Bar) {
        canny2Value = int.Parse(_canny2MinValue.text) + canny2Bar * (int.Parse(_canny2MaxValue.text) - int.Parse(_canny2MinValue.text));
        _canny2Value.text = canny2Value.ToString();
        if (canny2Listeners.Count > 0) {
            foreach (TrackbarListener l in canny2Listeners) {
                l.Callback(canny2Value);
            }
        }
    }

    private void Threshold1Changed(float threshold1Bar) {
        threshold1Value = int.Parse(_threshold1MinValue.text) + threshold1Bar * (int.Parse(_threshold1MaxValue.text) - int.Parse(_threshold1MinValue.text));
        _threshold1Value.text = threshold1Value.ToString();
        if (threshold1Listeners.Count > 0) {
            foreach (TrackbarListener l in threshold1Listeners) {
                l.Callback(threshold1Value);
            }
        }
    }

    private void Threshold2Changed(float threshold2Bar) {
        threshold2Value = int.Parse(_threshold2MinValue.text) + threshold2Bar * (int.Parse(_threshold2MaxValue.text) - int.Parse(_threshold2MinValue.text));
        _threshold2Value.text = threshold2Value.ToString();
        if (threshold2Listeners.Count > 0) {
            foreach (TrackbarListener l in threshold2Listeners) {
                l.Callback(threshold2Value);
            }
        }
    }

    public void AddCanny1Listener(TrackbarListener l) {
        canny1Listeners.Add(l);
    }

    public void RemoveCanny1Listener(TrackbarListener l) {
        canny1Listeners.Remove(l);
    }

    public float GetCanny1Value() {
        return(canny1Value);
    }

    public void AddCanny2Listener(TrackbarListener l) {
        canny2Listeners.Add(l);
    }

    public void RemoveCanny2Listener(TrackbarListener l) {
        canny2Listeners.Remove(l);
    }

    public float GetCanny2Value() {
        return(canny2Value);
    }

    public void AddThreshold1Listener(TrackbarListener l) {
        threshold1Listeners.Add(l);
    }

    public void RemoveThreshold1Listener(TrackbarListener l) {
        threshold1Listeners.Remove(l);
    }

    public float GetThreshold1Value() {
        return(threshold1Value);
    }

    public void AddThreshold2Listener(TrackbarListener l) {
        threshold2Listeners.Add(l);
    }

    public void RemoveThreshold2Listener(TrackbarListener l) {
        threshold2Listeners.Remove(l);
    }

    public float GetThreshold2Value() {
        return(threshold2Value);
    }
}
