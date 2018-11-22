using System;
using System.Collections;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using UnityEngine;

public class AVMDll
{
    [DllImport("AVMDll")]
    public static extern int GetVersion();

    [DllImport("AVMDll")]
    public static extern void SetCVTexture(int index, int tex);

    [DllImport("AVMDll")]
    public static extern IntPtr GetRenderEventFunc();
}
