﻿using System.Collections;
using System.Collections.Generic;
using UnityEngine;
namespace cvBridge
{
    public class CVTexture : MonoBehaviour
    {

        public bool createOnWake = true;
        public int cvTexIndex = 1;
        public Texture2D texture;
        [Header("The size of the texture can be max to (2048x2048)")]
        public int width = 512;
        public int height = 512;


        private void Awake()
        {
            texture = new Texture2D(width, height, TextureFormat.ARGB32, false);
            CVBridge.SetCVTexture(cvTexIndex, width, height, texture.GetNativeTexturePtr().ToInt32());
            GetComponent<Renderer>().material.mainTexture = texture;
        }
    }
}
