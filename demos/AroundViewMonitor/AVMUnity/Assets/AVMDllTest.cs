using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class AVMDllTest : MonoBehaviour {

	// Use this for initialization
	void Start ()
    {
        int version = AVMDll.GetVersion();
        Debug.Log("avmdll version:" + version);
	}
	
	// Update is called once per frame
	void Update () {
		Graphics.Blit(
	}
}
