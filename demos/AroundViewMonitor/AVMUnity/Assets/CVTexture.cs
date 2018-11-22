using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CVTexture : MonoBehaviour {

    public bool createOnWake = true;
    public int cvTexIndex = 1;
    public Texture2D texture;
    public int width = 512;
    public int height = 512;
    

    private void Awake()
    {
        texture = new Texture2D(width, height, TextureFormat.RGBA32,false);
        AVMDll.SetCVTexture(cvTexIndex, texture.GetNativeTexturePtr().ToInt32());
        //GetComponent<Renderer>().material = new Material(GetComponent<Renderer>().material);
        GetComponent<Renderer>().sharedMaterial.mainTexture = texture;
    }
}
