using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class StereoCameraLocation
{
    public Vector3 position;
    public Quaternion rotation;
}

public class StereoCameraParameters
{
    
}

public class LoacatingCamera : MonoBehaviour
{
    public Texture leftEyeTexture;
    public Texture rightEyeTexture;
    
    public Transform leftCamera;
    public Transform rightCamera;
    public Transform middleCamera;
    public Transform featureRoot;
    public Transform[] features;


    public void Start()
    {
        features = new Transform[featureRoot.childCount];
        for (int i = 0; i < featureRoot.childCount; i++)
        {
            features[i] = featureRoot.GetChild(i);
        }

    }


    public bool UpdateCamerasLocation(out StereoCameraLocation cameraLocation1, StereoCameraLocation cameraLocation0,
        int featureCount, StereoCameraLocation[] featureLocations1, StereoCameraLocation[] featureLocations0,
        StereoCameraParameters camerParam)
    {
        cameraLocation1 = new StereoCameraLocation();
        return false;
    }

    private void Update()
    {
        
    }

    private void LateUpdate()
    {
        StereoCameraLocation cameraLocation1;
        StereoCameraLocation cameraLocation0 = new StereoCameraLocation();
        StereoCameraLocation[] featureLocations1 = new StereoCameraLocation[5];
        StereoCameraLocation[] featureLocations0 = new StereoCameraLocation[5];
        StereoCameraParameters camerParam = new StereoCameraParameters();


        if (UpdateCamerasLocation(out cameraLocation1, cameraLocation0, featureLocations0.Length, featureLocations1, featureLocations0, camerParam))
        {
            transform.position = cameraLocation1.position;
            transform.rotation = cameraLocation1.rotation;
        }


    }


}
