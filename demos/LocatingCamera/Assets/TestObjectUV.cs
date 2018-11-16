using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TestObjectUV : MonoBehaviour
{
    public Transform Target;
    public Camera camera;

    public Vector2 GetUV()
    {   
        Vector4 world = new Vector4(Target.position.x, Target.position.y, Target.position.z, 1);
        Debug.Log(string.Format("world:{0:F5},{1:F5},{2:F5},{3:F5},",world.x, world.y, world.z, world.w));

        Vector3 viewportPoint = camera.WorldToViewportPoint(world);
        Debug.Log(string.Format("viewportPoint:{0:F5},{1:F5},{2:F5}", viewportPoint.x, viewportPoint.y, viewportPoint.z));

        Matrix4x4 w2v = camera.worldToCameraMatrix;
        Debug.Log("w2v:" + w2v);
        Matrix4x4 proj = camera.projectionMatrix;
        Debug.Log("proj:" + proj);

        Vector4 view = w2v * world;
        Debug.Log(string.Format("view:{0:F5},{1:F5},{2:F5},{3:F5},", view.x, view.y, view.z, view.w));

        Vector4 clip = proj * view ;
        Debug.Log(string.Format("clip:{0:F5},{1:F5},{2:F5},{3:F5},", clip.x, clip.y, clip.z, clip.w));


        Vector4 normalClip = clip / clip.w;
        Debug.Log("normalClip:" + normalClip);
        return new Vector2(normalClip.x, normalClip.y);
    }

    private void OnGUI()
    {
        if (GUI.Button(new Rect(100,0,100,100),"GetUV"))
        {
            Vector2 uv = GetUV();
            Debug.Log(string.Format("uv:{0:F5},{1:F5},", uv.x, uv.y));
            Debug.Log("uv:" + uv);
        }
    }


}
