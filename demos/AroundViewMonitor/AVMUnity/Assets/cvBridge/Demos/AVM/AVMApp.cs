using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using cvBridge;

public class AVMApp : MonoBehaviour {


    private void Start()
    {
        StartCoroutine(CallPluginAtEndOfFrames());
    }
    


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
            GL.IssuePluginEvent(CVBridge.GetRenderEventFunc(), 1);
        }
    }
}
