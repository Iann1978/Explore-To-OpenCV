using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace cvBridge
{
    [RequireComponent(typeof(Camera))]
    public class CVRenderTexture : MonoBehaviour
    {
        public int cvTexIndex = 0;
        public int width = 512;
        public int height = 512;
        RenderTexture rtx;

        private void Awake()
        {
            RenderTextureDescriptor rtxDesc = new RenderTextureDescriptor(512, 256);
            rtx = new RenderTexture(rtxDesc);
            rtx.Create();
            Camera camera = GetComponent<Camera>();
            camera.targetTexture = rtx;
            AVMDll.SetCVTexture(cvTexIndex, rtx.GetNativeTexturePtr().ToInt32());
        }
    }
}
