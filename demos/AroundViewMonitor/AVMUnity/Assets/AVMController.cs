using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using cvBridge;

//[ExecuteInEditMode]
public class AVMController : MonoBehaviour
{
    public Camera frontCamera;
    public CVTexture cvTexture;

    public float w = 1.8f;
    public float h = 6.0f;
    public float wf = 8.0f;
    public float hf = 16.0f;
    public float Hf = 256;
    

    [Header("the property below is calculated.")]
    public float Wf;
    public float Ht;
    public float Wt;
    public float l;
    public float fovV, fovHH,fovH;
    public float fovVDegree;
    public float fovHDegree;
    public float ratio;

    public int a, b;

    [ContextMenu("Calculate")]
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
        Ht = Hf / hf * (hf + hf + h);
        Wt = Ht / (hf + hf + h) * wf;

        fovVDegree = fovV * Mathf.Rad2Deg;
        fovHDegree = fovH * Mathf.Rad2Deg;

        a = (int)(hf / (h + hf + hf) * Ht);
        b = (int)((wf - w) / 2 / wf * Wt);

        frontCamera.transform.position = new Vector3(0.0f, l, -h / 2);
        frontCamera.transform.rotation = Quaternion.EulerRotation(Mathf.PI / 2 + fovV / 2, 0, 0);
        frontCamera.fieldOfView = Mathf.Rad2Deg * fovV;

        CVRenderTexture rt = frontCamera.GetComponent<CVRenderTexture>();
        if (rt)
        {
            rt.width = (int)Wf;
            rt.height = (int)Hf;
        }
        cvTexture.width = (int)Wt;
        cvTexture.height = (int)Ht;
    }


    void Awake()
    {

        CvBridgeDll.SetInteger(0, a);
        CvBridgeDll.SetInteger(1, b);
        CvBridgeDll.SetInteger(2, (int)Wf);
        CvBridgeDll.SetInteger(3, (int)Hf);
        CvBridgeDll.SetInteger(4, (int)Wt);
        CvBridgeDll.SetInteger(5, (int)Ht);
    }
    //public void Update()
    //{
    //    Calculate();
    //    frontCamera.transform.position = new Vector3(0.0f, l, -h / 2);
    //    frontCamera.transform.rotation = Quaternion.EulerRotation(Mathf.PI/2+fovV/2, 0, 0);
    //    frontCamera.fieldOfView = Mathf.Rad2Deg*fovV;

    //    //if (frontCamera.targetTexture.width
    //    int tmp = Wf;
    //    if (frontCamera.targetTexture == null || tmp != frontCamera.targetTexture.width)
    //        frontCamera.targetTexture = RenderTexture.GetTemporary(Wf, Hf);
    //    //frontCamera.targetTexture.width = Wf;
    //}

    


}
