using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class AVMController : MonoBehaviour
{
    public float w = 1.8f;
    public float h = 6.0f;
    public float wf = 8.0f;
    public float hf = 16.0f;
    public int Hf = 256;
    public int Ht = 1024;

    [Header("the property below is calculated.")]
    public int Wf;
    public int Wt;
    public float l;
    public float fovV, fovHH,fovH;
    public float ratio;

    void Calculate()
    {
        l = Mathf.Sqrt(hf * hf / (wf * wf - w * w));
        fovV = Mathf.Atan(hf / l);
        fovHH = 2 * Mathf.Atan(w / 2 / l);
        fovH = 2 * Mathf.Atan(Mathf.Tan(fovHH / 2) * Mathf.Tan(fovV / 2));
        ratio = Mathf.Tan(fovH / 2) / Mathf.Tan(fovV / 2);
        Wf = (int)(Hf * ratio);
        Wt = (int)(Ht * Wf / (h + hf + hf));
    }

    public void Update()
    {
        Calculate();
    }



}
