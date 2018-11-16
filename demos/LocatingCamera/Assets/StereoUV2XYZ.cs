using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class StereoUV2XYZ : MonoBehaviour
{
    public Camera leftCamera;
    public Camera rightCamera;
    public Transform feature;
    
    public Vector3 WorldToUV(Vector3 pw, Camera camera)
    {
        Vector4 world = new Vector4(pw.x, pw.y, pw.z, 1);
        //Debug.Log(string.Format("world:{0:F5},{1:F5},{2:F5},{3:F5},", world.x, world.y, world.z, world.w));

        Vector3 viewportPoint = camera.WorldToViewportPoint(world);
        //Debug.Log(string.Format("viewportPoint:{0:F5},{1:F5},{2:F5}", viewportPoint.x, viewportPoint.y, viewportPoint.z));

        Matrix4x4 w2v = camera.worldToCameraMatrix;
        //Debug.Log("w2v:" + w2v);
        Matrix4x4 proj = camera.projectionMatrix;
        //Debug.Log("proj:" + proj);

        Vector4 view = w2v * world;
        //Debug.Log(string.Format("view:{0:F5},{1:F5},{2:F5},{3:F5},", view.x, view.y, view.z, view.w));

        Vector4 clip = proj * view;
        //Debug.Log(string.Format("clip:{0:F5},{1:F5},{2:F5},{3:F5},", clip.x, clip.y, clip.z, clip.w));


        Vector4 normalClip = clip / clip.w;
        //Debug.Log("normalClip:" + normalClip);

        Vector2 screen = new Vector2(camera.pixelWidth * (0.5f + normalClip.x * 0.5f), camera.pixelHeight * (0.5f + normalClip.y * 0.5f));
        Debug.Log(string.Format("screen:{0:F5},{1:F5},", screen.x, screen.y));

        return screen;
    }
    

    public void Calculate()
    {
        Vector2 uvl = WorldToUV(feature.position, leftCamera);
        Vector2 uvr = WorldToUV(feature.position, rightCamera);

        float d = 1;
        float ur = uvr.x;
        float ul = uvl.x;
        float w = rightCamera.pixelWidth;
        float h = rightCamera.pixelHeight;
        float xr = d * (2 * ur - w) / ((2 * ul - w) - (2 * ur - w));
        Debug.Log(string.Format("xr:{0:F5},", xr));

        float fov = 60 * Mathf.Deg2Rad;

        float zr = xr * w / (2 * ur - w) / Mathf.Tan(fov / 2);
        Debug.Log(string.Format("zr:{0:F5},", zr));

        float vr = uvr.y;

        float yr = zr * (2 * vr - h) * Mathf.Tan(fov / 2) / h;
        Debug.Log(string.Format("yr:{0:F5},", yr));
    }

    private void OnGUI()
    {
        if (GUI.Button(new Rect(200, 0, 100, 100), "WorldToUVLeft"))
        {
            WorldToUV(feature.position, leftCamera);
        }

        if (GUI.Button(new Rect(200, 100, 100, 100), "Calculate"))
        {
            Calculate();
        }
    }


}
