using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace cvBridge
{
    public class CVInteger : MonoBehaviour
    {
        public int cvIntIndex = 0;
        public int intValue = 0;

        public void Awake()
        {
            CvBridgeDll.SetInteger(cvIntIndex, intValue);
        }

        // Update is called once per frame
        void Update()
        {
            CvBridgeDll.SetInteger(cvIntIndex, intValue);
        }
    }
}