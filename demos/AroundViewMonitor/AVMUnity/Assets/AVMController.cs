using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[ExecuteInEditMode]
public class AVMController : MonoBehaviour
{
    public Camera frontCamera;

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
    public float fovVDegree;
    public float fovHDegree;
    public float ratio;

    void Calculate()
    {
        l = Mathf.Sqrt(w*w*hf * hf / (wf * wf - w * w));
        fovV = Mathf.Atan(hf / l);
        fovHH = 2 * Mathf.Atan(w / 2 / l);
        fovH = 2*Mathf.Atan(Mathf.Sqrt((Mathf.Tan(fovHH / 2) * Mathf.Tan(fovHH / 2) * (Mathf.Tan(fovV / 2) * Mathf.Tan(fovV / 2) + 1))));
        //fovH = 2 * Mathf.Atan(Mathf.Tan(fovHH / 2) * Mathf.Tan(fovV / 2));
        //fovH = fovHH;
        ratio = Mathf.Tan(fovH / 2) / Mathf.Tan(fovV / 2);
        Wf = (int)(Hf * ratio);
        Wt = (int)(Ht * Wf / (h + hf + hf));

        fovVDegree = fovV * Mathf.Rad2Deg;
        fovHDegree = fovH * Mathf.Rad2Deg;
    }

    public void Update()
    {
        Calculate();
        frontCamera.transform.position = new Vector3(0.0f, l, -h / 2);
        frontCamera.transform.rotation = Quaternion.EulerRotation(Mathf.PI/2+fovV/2, 0, 0);
        frontCamera.fieldOfView = Mathf.Rad2Deg*fovV;

        //if (frontCamera.targetTexture.width
        int tmp = Wf;
        if (tmp != frontCamera.targetTexture.width)
        frontCamera.targetTexture = RenderTexture.GetTemporary(Wf, Hf);
        //frontCamera.targetTexture.width = Wf;
    }

    


}
