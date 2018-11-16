using System.Collections;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using UnityEngine;

public class EigenSharp
{

    [DllImport("EigenSharp")]
    public static extern float getTrace();

    [DllImport("EigenSharp")]
    public unsafe static extern bool cal_line_equation(float* x, int m, int n, float* M, float* N);

    public static bool cal_line_equation(ref float[] x, int m, int n, float[] M, float[] N)
    {
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
        return ret;
    }
}
