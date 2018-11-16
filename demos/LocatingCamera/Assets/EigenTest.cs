
using System.Collections;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using UnityEngine;

public class EigenTest : MonoBehaviour
{
    [DllImport("EigenSharp")]
    public static extern float getTrace();

    [DllImport("EigenSharp")]
    public unsafe static extern bool cal_line_equation(float* x, int m, int n, float* M, float* N);
    
    void Start()
    {
        int m = 3; int n = 2;
        float[] x = new float[2]; x[0] = 0; x[1] = 1;
        float[] M = new float[m * n];
        M[0 * n + 0] = UnityEngine.Random.Range(0.0f, 1.0f); M[0 * n + 1] = UnityEngine.Random.Range(0.0f, 1.0f);
        M[1 * n + 0] = UnityEngine.Random.Range(0.0f, 1.0f); M[1 * n + 1] = UnityEngine.Random.Range(0.0f, 1.0f);
        M[2 * n + 0] = UnityEngine.Random.Range(0.0f, 1.0f); M[2 * n + 1] = UnityEngine.Random.Range(0.0f, 1.0f);
        float[] N = new float[m];
        N[0] = UnityEngine.Random.Range(0.0f, 1.0f);
        N[1] = UnityEngine.Random.Range(0.0f, 1.0f);
        N[2] = UnityEngine.Random.Range(0.0f, 1.0f);



        bool ret = false;

        unsafe
        {
            fixed (float* xx = x)
            fixed (float* MM = M)
            fixed (float* NN = N)
            {
                ret = cal_line_equation(xx, m, n, MM, NN);
            }
        }

        Debug.Log("x:" + x);
        Debug.Log("M:" + M);
        Debug.Log("N:" + N);
        test_cal_line_equation();
        //Debug.Log("The trace value is: " + getTrace());
    }

    void test_cal_line_equation()
    {
        float a = 1.2f;
        float b = 2.2f;
        Vector3[] points;

        Debug.Log("before a: " + a + " b: " + b);
        GenLinePoint(out points, 100, 1.2f, 2.2f);
        for (int i = 0; i < points.Length; i++)
        {
            points[i].x += Random.RandomRange(-0.5f, 0.5f);
            points[i].y += Random.RandomRange(-0.5f, 0.5f);
            points[i].z += Random.RandomRange(-0.5f, 0.5f);
        }
        a = 0; b = 0;
        FilterLine(out a, out b, points);
        Debug.Log("after a: " + a + " b: " + b);

    }


    /// <summary>
    /// z = a*x + b*y
    /// </summary>
    /// <param name="points"></param>
    /// <param name="m"></param>
    /// <param name="a"></param>
    /// <param name="b"></param>
    void GenLinePoint(out Vector3[] points, int m, float a, float b)
    {
        points = new Vector3[m];
        for (int i = 0; i < m; i++)
        {
            float x = Random.RandomRange(0.0f, 100.0f);
            float y = Random.RandomRange(0.0f, 100.0f);
            float z = a * x + b * y;
            points[i] = new Vector3(x, y, z);
        }
    }

    void FilterLine(out float a, out float b, Vector3[] points)
    {
        int m = points.Length;
        int n = 2;
        float[] x = new float[n];
        float[] M = new float[m * n];
        float[] N = new float[m];
        for (int r = 0; r < m; r++)
        {
            M[r * n + 0] = points[r].x;
            M[r * n + 1] = points[r].y;
            N[r] = points[r].z;
        }
        unsafe
        {
            fixed (float* xx = x)
            fixed (float* MM = M)
            fixed (float* NN = N)
            {
                cal_line_equation(xx, m, n, MM, NN);
            }
        }
        a = x[0];
        b = x[1];
    }

}