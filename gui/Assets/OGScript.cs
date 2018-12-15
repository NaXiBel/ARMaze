using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class OGScript : MonoBehaviour {
    
    double width;
    double height;
    RectTransform rectTransform; 
    public RectTransform canvas;

    int dx;
    int dy;

	// Use this for initialization
	void Start () {
        rectTransform = GetComponent<RectTransform>();
        width = canvas.rect.width;
        height = canvas.rect.height;
        dx = 1;
        dy = 1;
	}
	
	// Update is called once per frame
	void Update () {
        float x = rectTransform.anchoredPosition.x;
        float y = rectTransform.anchoredPosition.y;

        if(x - 50 <= -width/2)
            dx = 1;

        if(x + 50 >= width/2)
            dx = -1;

        if(y - 50 <= -height/2)
            dy = 1;

        if(y + 50 >= height/2)
            dy = -1;

        rectTransform.anchoredPosition += new Vector2(dx, dy);

    }

}
