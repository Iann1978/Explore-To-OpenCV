using System.Collections;
using System.Collections.Generic;
using System.IO;
using UnityEngine;

public class SaveDisplay : MonoBehaviour {

    public Camera leftCamera;
    public Camera rightCamera;


    public IEnumerator SaveCamera(Camera camera, string filename)
    {
        yield return new WaitForEndOfFrame();
        int width = camera.pixelWidth;
        int height = camera.pixelHeight;
        Texture2D tex = new Texture2D(width, height);
        tex.ReadPixels(new Rect(0, 0, width, height), 0, 0, false);
        byte[] bytes = tex.EncodeToPNG();
        Destroy(tex);
        File.WriteAllBytes(filename, bytes);
    }

    public void Update()
    {
        if (Input.GetKeyDown(KeyCode.L))
        {
            StartCoroutine(SaveCamera(leftCamera, "E:/LeftCamera.png"));
        }
        if (Input.GetKeyDown(KeyCode.R))
        {
            StartCoroutine(SaveCamera(rightCamera, "E:/RightCamera.png"));
        }
    }

    private void OnGUI()
    {
        return;
        if (GUI.Button(new Rect(300, 0, 100, 100), "SaveLeftCamera"))
        {
            StartCoroutine(SaveCamera(leftCamera, "E:/LeftCamera.png"));
        }

        if (GUI.Button(new Rect(300, 100, 100, 100), "SaveRightCamera"))
        {
            StartCoroutine(SaveCamera(rightCamera, "E:/RightCamera.png"));
        }

    }
}
