using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public static class MazeData {

    public static Vector3[,] ARRAY_DATAS_TEST = new Vector3[,] {
        {
            new Vector3(-5.0f, 0.0f, 5.0f),
            new Vector3(-2.0f, 0.0f, 5.0f)
        },
        {
            new Vector3(-2.0f, 0.0f, 5.0f),
            new Vector3(-2.0f, 0.0f, 3.0f)
        },
        {
            new Vector3(-2.0f, 0.0f, 3.0f),
            new Vector3(1.0f, 0.0f, 3.0f)
        },
        {
            new Vector3(1.0f, 0.0f, 3.0f),
            new Vector3(1.0f, 0.0f, 1.0f)
        },
        {
            new Vector3(3.0f, 0.0f, 4.0f),
            new Vector3(5.0f, 0.0f, 2.0f)
        },
        {
            new Vector3(5.0f, 0.0f, 2.0f),
            new Vector3(5.0f, 0.0f, -1.0f)
        },
        {
            new Vector3(5.0f, 0.0f, -3.0f),
            new Vector3(3.0f, 0.0f, -4.0f)
        },
        {
            new Vector3(2.0f, 0.0f, -1.0f),
            new Vector3(2.0f, 0.0f, -3.0f)
        },
        {
            new Vector3(0.0f, 0.0f, -3.0f),
            new Vector3(-4.0f, 0.0f, -3.0f)
        },
        {
            new Vector3(0.0f, 0.0f, -1.0f),
            new Vector3(-2.0f, 0.0f, -1.0f)
        },
        {
            new Vector3(-2.0f, 0.0f, -1.0f),
            new Vector3(-2.0f, 0.0f, 1.0f)
        },
        {
            new Vector3(-4.0f, 0.0f, -1.0f),
            new Vector3(-4.0f, 0.0f, 1.0f)
        }
    };

    public static Vector3 MAZE_POINT_OF_ARRIVAL = new Vector3(-0.5f, 0.5f, 4.5f);

}
