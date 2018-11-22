using System;
using System.Collections;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using UnityEngine;

[RequireComponent(typeof(Camera))]
public class RenderToCVTexture : MonoBehaviour
{
    public int cvTexIndex = 0;
    public RenderTexture rtx;

    private void Awake()
    {
        RenderTextureDescriptor rtxDesc = new RenderTextureDescriptor(512,256);
        

        rtx = new RenderTexture(rtxDesc);

        Camera camera = GetComponent<Camera>();

        camera.targetTexture = rtx;

        AVMDll.SetCVTexture(cvTexIndex, rtx.GetNativeTexturePtr().ToInt32());

        StartCoroutine(CallPluginAtEndOfFrames());

    }


    //public void Update()
    //{
    //    GL.IssuePluginEvent(AVMDll.GetRenderEventFunc(), 1);
    //}


    private IEnumerator CallPluginAtEndOfFrames()
    {
        while (true)
        {
            // Wait until all frame rendering is done
            yield return new WaitForEndOfFrame();

            // Set time for the plugin
            //SetTimeFromUnity(Time.timeSinceLevelLoad);

            // Issue a plugin event with arbitrary integer identifier.
            // The plugin can distinguish between different
            // things it needs to do based on this ID.
            // For our simple plugin, it does not matter which ID we pass here.
            GL.IssuePluginEvent(AVMDll.GetRenderEventFunc(), 1);
        }
    }

}
