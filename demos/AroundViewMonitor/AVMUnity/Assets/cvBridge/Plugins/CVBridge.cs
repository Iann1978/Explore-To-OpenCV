using System;
using System.Collections;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using UnityEngine;

namespace cvBridge
{
    public class CVBridge
    {
        [DllImport("CVBridge")]
        public static extern int GetVersion();

        [DllImport("CVBridge")]
        public static extern void SetCVTexture(int index, int width, int height, int tex);

        [DllImport("CVBridge")]
        public static extern void SetInteger(int index, int value);

        [DllImport("CVBridge")]
        public static extern IntPtr GetRenderEventFunc();
    }
}
