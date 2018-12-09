using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using cvBridge;
using System;

[Serializable]
class CameraParameter
{
    public float farWidth, nearWidth;
    public float farDis;
    public float fovV, fovH;
    public float disToEarth;
    public float ratio;
    public float texWidth, texHeight;
}

//[ExecuteInEditMode]
public class AVMController : MonoBehaviour
{
    public Camera frontCamera;
    public Camera leftCamera;
    public Camera rightCamera;
    public Camera backCamera;

    public CVTexture cvTexture;

    public float w = 1.8f;
    public float h = 6.0f;
    public float wext = 8.0f;
    public float hext = 16.0f;

    public float texHeight = 1024;
    public float texWidth;


    [SerializeField]
    CameraParameter frontCameraParam;
    [SerializeField]
    CameraParameter leftCameraParam;
    [SerializeField]
    CameraParameter rightCameraParam;
    [SerializeField]
    CameraParameter backCameraParam;



    [ContextMenu("CalculateTextureWidth")]
    void CalculateTextureWidth()
    {
        texWidth = texHeight * (w + wext + wext) / (h + hext + hext);
    }

    void CalCamera(float wt, float wb,  float h, ref float l, ref float fovV, ref float fovH, ref float ratio)
    {
        l = Mathf.Sqrt(wb * wb * h * h / (wt * wt - wb * wb));
        fovV = Mathf.Atan(h / l);
        float fovHH = 2 * Mathf.Atan(wb / 2 / l);
        fovH = 2 * Mathf.Atan(Mathf.Sqrt((Mathf.Tan(fovHH / 2) * Mathf.Tan(fovHH / 2) * (Mathf.Tan(fovV / 2) * Mathf.Tan(fovV / 2) + 1))));
        ratio = Mathf.Tan(fovH / 2) / Mathf.Tan(fovV / 2);

    }


    [ContextMenu("CalculateFrontCamera")]
    void CalculateFrontCamera()
    {
        Camera camera = frontCamera;
        CameraParameter param = frontCameraParam;

        param.farWidth = w + wext + wext;
        param.nearWidth = w;
        param.farDis = hext;

        CalCamera(param.farWidth, param.nearWidth, param.farDis,
            ref param.disToEarth, ref param.fovV, ref param.fovH, ref param.ratio);
        param.texHeight = 256;
        param.texWidth = param.texHeight * param.ratio;


        camera.transform.position = new Vector3(0, param.disToEarth, -h/2);
        camera.transform.rotation = Quaternion.EulerRotation(Mathf.PI / 2 + param.fovV / 2, 0, 0);
        camera.fieldOfView = Mathf.Rad2Deg * param.fovV;
        CVRenderTexture rt = camera.GetComponent<CVRenderTexture>();
        if (rt)
        {
            rt.width = (int)param.texWidth;
            rt.height = (int)param.texHeight;
        }
    }

    [ContextMenu("CalculateBackCamera")]
    void CalculateBackCamera()
    {
        Camera camera = backCamera;
        CameraParameter param = backCameraParam;

        param.farWidth = w + wext + wext;
        param.nearWidth = w;
        param.farDis = hext;

        CalCamera(param.farWidth, param.nearWidth, param.farDis,
            ref param.disToEarth, ref param.fovV, ref param.fovH, ref param.ratio);
        param.texHeight = 256;
        param.texWidth = param.texHeight * param.ratio;


        camera.transform.position = new Vector3(0, param.disToEarth, h / 2);
        camera.transform.rotation = Quaternion.EulerRotation(Mathf.PI / 2 - param.fovV / 2, 0, 0);
        camera.fieldOfView = Mathf.Rad2Deg * param.fovV;
        CVRenderTexture rt = camera.GetComponent<CVRenderTexture>();
        if (rt)
        {
            rt.width = (int)param.texWidth;
            rt.height = (int)param.texHeight;
        }
    }

    [ContextMenu("CalculateLeftCamera")]
    void CalculateLeftCamera()
    {

        Camera camera = leftCamera;
        CameraParameter param = leftCameraParam;

        param.farWidth = hext + hext + h;
        param.nearWidth = h;
        param.farDis = wext;

        CalCamera(param.farWidth, param.nearWidth, param.farDis,
            ref param.disToEarth, ref param.fovV, ref param.fovH, ref param.ratio);
        param.texHeight = 256;
        param.texWidth = param.texHeight * param.ratio;

        camera.transform.position = new Vector3(-w/2, param.disToEarth, 0);
        camera.transform.rotation = Quaternion.EulerRotation(Mathf.PI / 2+ param.fovV/2, Mathf.PI/2, 0);
        camera.fieldOfView = Mathf.Rad2Deg * param.fovV;
        CVRenderTexture rt = camera.GetComponent<CVRenderTexture>();
        if (rt)
        {
            rt.width = (int)param.texWidth;
            rt.height = (int)param.texHeight;
        }

    }

    [ContextMenu("CalculateRightCamera")]
    void CalculateRightCamera()
    {

        Camera camera = rightCamera;
        CameraParameter param = rightCameraParam;

        param.farWidth = hext + hext + h;
        param.nearWidth = h;
        param.farDis = wext;

        CalCamera(param.farWidth, param.nearWidth, param.farDis,
            ref param.disToEarth, ref param.fovV, ref param.fovH, ref param.ratio);
        param.texHeight = 256;
        param.texWidth = param.texHeight * param.ratio;

        camera.transform.position = new Vector3(w / 2, param.disToEarth, 0);
        camera.transform.rotation = Quaternion.EulerRotation(Mathf.PI / 2 + param.fovV / 2, -Mathf.PI / 2, 0);
        camera.fieldOfView = Mathf.Rad2Deg * param.fovV;
        CVRenderTexture rt = camera.GetComponent<CVRenderTexture>();
        if (rt)
        {
            rt.width = (int)param.texWidth;
            rt.height = (int)param.texHeight;
        }

    }

    [ContextMenu("CalculateAllCameras")]
    void CalculateAllCameras()
    {
        CalculateFrontCamera();
        CalculateLeftCamera();
        CalculateRightCamera();
        CalculateBackCamera();
    }

    void Awake()
    {

        CVBridge.SetInteger(0, (int)w);
        CVBridge.SetInteger(1, (int)h);
        CVBridge.SetInteger(2, (int)wext);
        CVBridge.SetInteger(3, (int)hext);
        //CvBridgeDll.SetInteger(4, (int)Wt);
        //CvBridgeDll.SetInteger(5, (int)Ht);
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
