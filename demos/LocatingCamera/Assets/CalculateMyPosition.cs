using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CalculateMyPosition : MonoBehaviour
{
    public Camera leftCamera;
    public Camera rightCamera;
    public Transform features;
    public Transform point;

    public void TestUV()
    {
        Vector3 view = WorldToView(point.position, leftCamera);
        Debug.Log("view:" + view);
        Vector3 uv = WorldToClip(point.position, leftCamera);
        Debug.Log("uv:" + uv);
    }

    public Vector3 WorldToView(Vector3 pw, Camera camera)
    {
        Matrix4x4 mx = camera.worldToCameraMatrix;
        
        Vector4 world = new Vector4(pw.x, pw.y, pw.z, 1);
        Vector4 view = mx * world;
        view /= view.w;
        return new Vector3(view.x, view.y, view.z);
    }

    public Vector3 WorldToClip(Vector3 pw, Camera camera)
    {
        Vector4 world = new Vector4(pw.x, pw.y, pw.z, 1);
        //Debug.Log(string.Format("world:{0:F5},{1:F5},{2:F5},{3:F5},", world.x, world.y, world.z, world.w));

        Vector3 viewportPoint = camera.WorldToViewportPoint(world);
        //Debug.Log(string.Format("viewportPoint:{0:F5},{1:F5},{2:F5}", viewportPoint.x, viewportPoint.y, viewportPoint.z));

        Matrix4x4 w2v = camera.worldToCameraMatrix;
        //Debug.Log("w2v:" + w2v);
        Matrix4x4 proj = camera.projectionMatrix;
        //Debug.Log("proj:" + proj);

        Vector4 view = w2v * world;
        //Debug.Log(string.Format("view:{0:F5},{1:F5},{2:F5},{3:F5},", view.x, view.y, view.z, view.w));

        Vector4 clip = proj * view;
        //Debug.Log(string.Format("clip:{0:F5},{1:F5},{2:F5},{3:F5},", clip.x, clip.y, clip.z, clip.w));


        Vector4 normalClip = clip / clip.w;
        //Debug.Log("normalClip:" + normalClip);
        return new Vector2(normalClip.x, normalClip.y);
    }


    //public void PrepareData(out int m, out int n, out float[] M, out float[] N,  Vector3[] points)
    //{
    //    int eqC = 4;
    //    m = points.Length * eqC;
    //    n = 24;
    //    M = new float[m * n];
    //    N = new float[m];
    //    for (int i = 0; i < M.Length; i++)
    //    {
    //        M[i] = 0;
    //    }

    //    for (int i = 0; i < N.Length; i++)
    //    {
    //        N[i] = 0;
    //    }

    //    for (int i = 0; i < points.Length; i++)
    //    {
    //        Vector3 pw = points[i];
    //        Vector3 pl = WorldToClip(pw,leftCamera);
    //        Vector3 pr = WorldToClip(pw,rightCamera);

    //        float random = Random.Range(0.5f, 1.0f);
    //        random = 1.0f;

    //        /******************
    //         * LM00 LM01 LM02 LM03
    //         * LM10 LM11 LM12 LM13
    //         ******************/

    //        //vl*xl'-ul*yl'=0
    //        M[(i * 4 + 0) * n + 0] = pl.y * pw.x * random;
    //        M[(i * 4 + 0) * n + 1] = pl.y * pw.y * random;
    //        M[(i * 4 + 0) * n + 2] = pl.y * pw.z * random;
    //        M[(i * 4 + 0) * n + 3] = pl.y * random;
    //        M[(i * 4 + 0) * n + 4] = -pl.x * pw.x * random;
    //        M[(i * 4 + 0) * n + 5] = -pl.x * pw.y * random;
    //        M[(i * 4 + 0) * n + 6] = -pl.x * pw.z * random;
    //        M[(i * 4 + 0) * n + 7] = -pl.x * random;
    //        N[i * 4 + 0] = 0;

    //        //vr*xr'-ur*yr'=0
    //        M[(i * 4 + 1) * n + 12] = pr.y * pw.x;
    //        M[(i * 4 + 1) * n + 13] = pr.y * pw.y;
    //        M[(i * 4 + 1) * n + 14] = pr.y * pw.z;
    //        M[(i * 4 + 1) * n + 15] = pr.y;
    //        M[(i * 4 + 1) * n + 16] = -pr.x * pw.x;
    //        M[(i * 4 + 1) * n + 17] = -pr.x * pw.y;
    //        M[(i * 4 + 1) * n + 18] = -pr.x * pw.z;
    //        M[(i * 4 + 1) * n + 19] = -pr.x;
    //        N[i * 4+ 1] = 0;


    //        //xl'-xr'=1
    //        M[(i * 4 + 2) * n + 0] = pw.x;
    //        M[(i * 4 + 2) * n + 1] = pw.y;
    //        M[(i * 4 + 2) * n + 2] = pw.z;
    //        M[(i * 4 + 2) * n + 3] = 1;
    //        M[(i * 4 + 2) * n + 12] = -pw.x;
    //        M[(i * 4 + 2) * n + 13] = -pw.y;
    //        M[(i * 4 + 2) * n + 14] = -pw.z;
    //        M[(i * 4 + 2) * n + 15] = -1;
    //        N[i * 4 + 2] = 1;

    //        //zl'=zr'
    //        M[(i * 4 + 3) * n + 8] = pr.y * pw.x;
    //        M[(i * 4 + 3) * n + 9] = pr.y * pw.y;
    //        M[(i * 4 + 3) * n + 10] = pr.y * pw.z;
    //        M[(i * 4 + 3) * n + 11] = pr.y;
    //        M[(i * 4 + 3) * n + 20] = -pr.x * pw.x;
    //        M[(i * 4 + 3) * n + 21] = -pr.x * pw.y;
    //        M[(i * 4 + 3) * n + 22] = -pr.x * pw.z;
    //        M[(i * 4 + 3) * n + 23] = -pr.x;
    //        N[i * 4 + 3] = 0;


    //    }
    //}

    struct PointData
    {
        public Vector3 pw;
        public Vector3 pl;
        public Vector3 pr;
    }

    PointData[] PreparePointData(Vector3[] points)
    {
        PointData[] pointDatas = new PointData[points.Length];
        for (int i = 0; i < points.Length; i++)
        {
            Vector3 pw = points[i];
            pointDatas[i].pw = pw;
            pointDatas[i].pl = WorldToClip(pw, leftCamera);
            pointDatas[i].pr = WorldToClip(pw, rightCamera);
        }
        return pointDatas;
    }

    Vector3[] GetFeaturePoints()
    {
        Vector3[] points = new Vector3[features.childCount];
        for (int i = 0; i < features.childCount; i++)
        {
            points[i] = features.GetChild(i).position;
        }
        return points;
    }

    void NewMNX(int m, int n, out float[] M, out float[] N, out float[] X)
    {
        M = new float[m * n];
        N = new float[m];
        X = new float[n];
        for (int i = 0; i < M.Length; i++)
        {
            M[i] = 0;
        }

        for (int i = 0; i < N.Length; i++)
        {
            N[i] = 0;
        }

        for (int i = 0; i < X.Length; i++)
        {
            X[i] = Mathf.NegativeInfinity;
        }
    }
    /*prepare data for m = [lm00 lm01 lm02 lm03 
                            lm10 lm11 lm12 lm13
                            rm00 rm01 rm02 rm03
                            rm10 rm11 rm12 rm13] */
    void PrepareData0(out int m, out int n, out float[] M, out float[] N, out float[] X, PointData[] pointDatas, float a)
    {
        int eqc = 4;//equation count
        m = pointDatas.Length * eqc;
        n = 16;
        NewMNX(m, n, out M, out N, out X);

        for (int i = 0; i < pointDatas.Length; i++)
        {
            Vector3 pw = pointDatas[i].pw;
            Vector3 pl = pointDatas[i].pl;
            Vector3 pr = pointDatas[i].pr;

            //u*y' = v*x' (v*x'- u*y'=0)
            M[(i * eqc + 0) * n + 0] = pl.y * pw.x;
            M[(i * eqc + 0) * n + 1] = pl.y * pw.y;
            M[(i * eqc + 0) * n + 2] = pl.y * pw.z;
            M[(i * eqc + 0) * n + 3] = pl.y;
            M[(i * eqc + 0) * n + 4] = -pl.x * pw.x;
            M[(i * eqc + 0) * n + 5] = -pl.x * pw.y;
            M[(i * eqc + 0) * n + 6] = -pl.x * pw.z;
            M[(i * eqc + 0) * n + 7] = -pl.x;
            N[i * eqc + 0] = 0;

            //u*y' = v*x'
            M[(i * eqc + 1) * n + 8] = pr.y * pw.x;
            M[(i * eqc + 1) * n + 9] = pr.y * pw.y;
            M[(i * eqc + 1) * n + 10] = pr.y * pw.z;
            M[(i * eqc + 1) * n + 11] = pr.y;
            M[(i * eqc + 1) * n + 12] = -pr.x * pw.x;
            M[(i * eqc + 1) * n + 13] = -pr.x * pw.y;
            M[(i * eqc + 1) * n + 14] = -pr.x * pw.z;
            M[(i * eqc + 1) * n + 15] = -pr.x;
            N[i * eqc + 1] = 0;

            //yl'-yr'=0
            M[(i * eqc + 3) * n + 4] = pw.x;
            M[(i * eqc + 3) * n + 5] = pw.y;
            M[(i * eqc + 3) * n + 6] = pw.z;
            M[(i * eqc + 3) * n + 7] = 1;
            M[(i * eqc + 3) * n + 12] = -pw.x;
            M[(i * eqc + 3) * n + 13] = -pw.y;
            M[(i * eqc + 3) * n + 14] = -pw.z;
            M[(i * eqc + 3) * n + 15] = -1;
            N[i * eqc + 2] = 0;

            //xl'-xr'=1
            M[(i * eqc + 2) * n + 0] = pw.x;
            M[(i * eqc + 2) * n + 1] = pw.y;
            M[(i * eqc + 2) * n + 2] = pw.z;
            M[(i * eqc + 2) * n + 3] = 1;
            M[(i * eqc + 2) * n + 8] = -pw.x;
            M[(i * eqc + 2) * n + 9] = -pw.y;
            M[(i * eqc + 2) * n + 10] = -pw.z;
            M[(i * eqc + 2) * n + 11] = -1;
            N[i * eqc + 2] = 2*a;
        }
    }

    // xl' = u*zl'
    void PrepareData1(out int m, out int n, out float[] M, out float[] N, out float[] X, PointData[] pointDatas, Matrix4x4 ML, Matrix4x4 MR)
    {
        int eqc = 6;//equation count
        m = pointDatas.Length * eqc;
        n = 8;
        NewMNX(m, n, out M, out N, out X);

        for (int i = 0; i < pointDatas.Length; i++)
        {
            Vector3 pw = pointDatas[i].pw;
            Vector3 pl = pointDatas[i].pl;
            Vector3 pr = pointDatas[i].pr;

            // ul*zl' = xl'
            M[(i * eqc + 0) * n + 0] = pl.x * pw.x;
            M[(i * eqc + 0) * n + 1] = pl.x * pw.y;
            M[(i * eqc + 0) * n + 2] = pl.x * pw.z;
            M[(i * eqc + 0) * n + 3] = pl.x;
            N[i * eqc + 0] = -(ML[0,0] * pw.x + ML[0,1] * pw.y + ML[0,2] * pw.z + ML[0,3]);

            // ur*zr' = xr'
            M[(i * eqc + 1) * n + 4] = pr.x * pw.x;
            M[(i * eqc + 1) * n + 5] = pr.x * pw.y;
            M[(i * eqc + 1) * n + 6] = pr.x * pw.z;
            M[(i * eqc + 1) * n + 7] = pr.x;
            N[i * eqc + 1] = -(MR[0, 0] * pw.x + MR[0, 1] * pw.y + MR[0, 2] * pw.z + MR[0, 3]);

            // zl' = zr'
            M[(i * eqc + 2) * n + 0] = pl.x * pw.x;
            M[(i * eqc + 2) * n + 1] = pl.x * pw.y;
            M[(i * eqc + 2) * n + 2] = pl.x * pw.z;
            M[(i * eqc + 2) * n + 3] = pl.x;
            M[(i * eqc + 2) * n + 4] = -pr.x * pw.x;
            M[(i * eqc + 2) * n + 5] = -pr.x * pw.y;
            M[(i * eqc + 2) * n + 6] = -pr.x * pw.z;
            M[(i * eqc + 2) * n + 7] = -pr.x;
            N[i * eqc + 2] = 0;

            M[(i * eqc + 3) * n + 0] = 1;
            M[(i * eqc + 3) * n + 4] = -1;
            N[i * eqc + 3] = 0;

            M[(i * eqc + 4) * n + 1] = 1;
            M[(i * eqc + 4) * n + 5] = -1;
            N[i * eqc + 4] = 0;

            M[(i * eqc + 5) * n + 2] = 1;
            M[(i * eqc + 5) * n + 6] = -1;
            N[i * eqc + 5] = 0;
        }
    }

    public void Caculate1()
    {
        Debug.Log(leftCamera.name + ":\n" + leftCamera.worldToCameraMatrix);
        Debug.Log(rightCamera.name + ":\n" + rightCamera.worldToCameraMatrix);

        Vector3[] points = GetFeaturePoints();
        PointData[] pointDatas = PreparePointData(points);

        Matrix4x4 ML = Matrix4x4.zero;
        Matrix4x4 MR = Matrix4x4.zero;
        int m, n; float[] M, N, X;

        /*prepare data for N = [lm00 lm01 lm02 lm03 
                        lm10 lm11 lm12 lm13
                        rm00 rm01 rm02 rm03
                        rm10 rm11 rm12 rm13] */
        PrepareData0(out m, out n, out M, out N, out X, pointDatas, 0.5f);
        EigenSharp.cal_line_equation(ref X, m, n, M, N);
        ML[0, 0] = X[0]; ML[0, 1] = X[1]; ML[0, 2] = X[2]; ML[0, 3] = X[3];
        MR[0, 0] = X[8]; MR[0, 1] = X[9]; MR[0, 2] = X[10]; MR[0, 3] = X[11];

        PrepareData1(out m, out n, out M, out N, out X, pointDatas, ML, MR);
        EigenSharp.cal_line_equation(ref X, m, n, M, N);
        ML[2, 0] = X[0]; ML[2, 1] = X[1]; ML[2, 2] = X[2]; ML[2, 3] = X[3];
        MR[2, 0] = X[4]; MR[2, 1] = X[5]; MR[2, 2] = X[6]; MR[2, 3] = X[7];

        Debug.Log("ML:\n" + ML);
        Debug.Log("MR:\n" + MR);

    }

    public void PrepareData(out int m, out int n, out float[] M, out float[] N, out float[] X, Vector3[] points)
    {
        int eqc = 4;//equation count
        m = points.Length * eqc;
        n = 16;
        NewMNX(m, n, out M, out N, out X);
        //M = new float[m * n];
        //N = new float[m];
        //for (int i = 0; i < M.Length; i++)
        //{
        //    M[i] = 0;
        //}

        //for (int i = 0; i < N.Length; i++)
        //{
        //    N[i] = 0;
        //}

        for (int i = 0; i < points.Length; i++)
        {
            Vector3 pw = points[i];
            Vector3 pl = WorldToClip(pw, leftCamera);
            Vector3 pr = WorldToClip(pw, rightCamera);

            //pw.x = pw.x * (1 + Random.Range(-0.1f, 0.1f));
            //pw.y = pw.y * (1 + Random.Range(-0.1f, 0.1f));
            //pw.z = pw.z * (1 + Random.Range(-0.1f, 0.1f));

            //pl.x = pl.x * (1 + Random.Range(-0.1f, 0.1f));
            //pl.y = pl.y * (1 + Random.Range(-0.1f, 0.1f));
            //pl.z = pl.z * (1 + Random.Range(-0.1f, 0.1f));

            //pr.x = pr.x * (1 + Random.Range(-0.1f, 0.1f));
            //pr.y = pr.y * (1 + Random.Range(-0.1f, 0.1f));
            //pr.z = pr.z * (1 + Random.Range(-0.1f, 0.1f));

            //float random = Random.Range(0.5f, 1.0f);
            //random = 1.0f;


            //u*y' = v*x'
            M[(i * eqc + 0) * n + 0] = pl.y * pw.x;
            M[(i * eqc + 0) * n + 1] = pl.y * pw.y;
            M[(i * eqc + 0) * n + 2] = pl.y * pw.z;
            M[(i * eqc + 0) * n + 3] = pl.y;
            M[(i * eqc + 0) * n + 4] = -pl.x * pw.x;
            M[(i * eqc + 0) * n + 5] = -pl.x * pw.y;
            M[(i * eqc + 0) * n + 6] = -pl.x * pw.z;
            M[(i * eqc + 0) * n + 7] = -pl.x;
            N[i * eqc + 0] = 0;

            //u*y' = v*x'
            M[(i * eqc + 1) * n + 8] = pr.y * pw.x;
            M[(i * eqc + 1) * n + 9] = pr.y * pw.y;
            M[(i * eqc + 1) * n + 10] = pr.y * pw.z;
            M[(i * eqc + 1) * n + 11] = pr.y;
            M[(i * eqc + 1) * n + 12] = -pr.x * pw.x;
            M[(i * eqc + 1) * n + 13] = -pr.x * pw.y;
            M[(i * eqc + 1) * n + 14] = -pr.x * pw.z;
            M[(i * eqc + 1) * n + 15] = -pr.x;
            N[i * eqc + 1] = 0;

            //yl'-yr'=0
            M[(i * eqc + 3) * n + 4] = pw.x;
            M[(i * eqc + 3) * n + 5] = pw.y;
            M[(i * eqc + 3) * n + 6] = pw.z;
            M[(i * eqc + 3) * n + 7] = 1;
            M[(i * eqc + 3) * n + 12] = -pw.x;
            M[(i * eqc + 3) * n + 13] = -pw.y;
            M[(i * eqc + 3) * n + 14] = -pw.z;
            M[(i * eqc + 3) * n + 15] = -1;
            N[i * eqc + 2] = 0;

            //xl'-xr'=1
            M[(i * eqc + 2) * n + 0] = pw.x;
            M[(i * eqc + 2) * n + 1] = pw.y;
            M[(i * eqc + 2) * n + 2] = pw.z;
            M[(i * eqc + 2) * n + 3] = 1;
            M[(i * eqc + 2) * n + 8] = -pw.x;
            M[(i * eqc + 2) * n + 9] = -pw.y;
            M[(i * eqc + 2) * n + 10] = -pw.z;
            M[(i * eqc + 2) * n + 11] = -1;
            N[i * eqc + 2] = 1f;


        }
    }
    public void Caculate()
    {
        Debug.Log(leftCamera.name + ":\n" + leftCamera.worldToCameraMatrix);
        Debug.Log(rightCamera.name + ":\n" + rightCamera.worldToCameraMatrix);
        
        Vector3[] points = new Vector3[features.childCount];
        for (int i = 0; i < features.childCount; i++)
        {
            points[i] = features.GetChild(i).position;
        }

        int m, n; float[] M, N, X;
        PrepareData(out m, out n, out M, out N,  out X, points);
        EigenSharp.cal_line_equation(ref X, m, n, M, N);


        Debug.Log(string.Format("{0:F5}:{1:F5}:{2:F5}:{3:F5}:", X[0], X[1], X[2], X[3]));
        Debug.Log(string.Format("{0:F5}:{1:F5}:{2:F5}:{3:F5}:", X[4], X[5], X[6], X[7]));
        Debug.Log(string.Format("{0:F5}:{1:F5}:{2:F5}:{3:F5}:", X[8], X[9], X[10], X[11]));
        Debug.Log(string.Format("{0:F5}:{1:F5}:{2:F5}:{3:F5}:", X[12], X[13], X[14], X[15]));
     //   Debug.Log(string.Format("{0:F5}:{1:F5}:{2:F5}:{3:F5}:", x[16], x[17], x[18], x[19]));
//        Debug.Log(string.Format("{0:F5}:{1:F5}:{2:F5}:{3:F5}:", x[20], x[21], x[22], x[23]));

        Vector3 RL0 = new Vector3(X[0], X[1], X[2]);
        Vector3 RL1 = new Vector3(X[4], X[5], X[6]);
        Vector3 RL2 = -Vector3.Cross(RL0, RL1);

        Vector3 RR0 = new Vector3(X[8], X[9], X[10]);
        Vector3 RR1 = new Vector3(X[12], X[13], X[14]);
        Vector3 RR2 = -Vector3.Cross(RR0, RR1);

        Matrix4x4 ML = Matrix4x4.zero;
        ML[0, 0] = RL0.x; ML[0, 1] = RL0.y; ML[0, 2] = RL0.z; ML[0, 3] = X[3];
        ML[1, 0] = RL1.x; ML[1, 1] = RL1.y; ML[1, 2] = RL1.z; ML[1, 3] = X[7];
        ML[2, 0] = RL2.x; ML[2, 1] = RL2.y; ML[2, 2] = RL2.z; ML[2, 3] = 0;
        ML[3, 0] = 0;     ML[3, 1] = 0;     ML[3, 2] = 0;     ML[3, 3] = 1;

        Matrix4x4 MR = Matrix4x4.zero;
        MR[0, 0] = RR0.x; MR[0, 1] = RR0.y; MR[0, 2] = RR0.z; MR[0, 3] = X[11];
        MR[1, 0] = RR1.x; MR[1, 1] = RR1.y; MR[1, 2] = RR1.z; MR[1, 3] = X[15];
        MR[2, 0] = RR2.x; MR[2, 1] = RR2.y; MR[2, 2] = RR2.z; MR[2, 3] = 0;
        MR[3, 0] = 0;     MR[3, 1] = 0;     MR[3, 2] = 0;     MR[3, 3] = 1;



        Vector3 pw = points[9];
        float xxl = ML[0, 0] * pw.x + ML[0, 1] * pw.y + ML[0, 2] * pw.z + ML[0, 3];
        //Debug.Log(string.Format("x':{0:F5}", xxl));
        float xxxl = Mathf.Tan(30 * Mathf.Deg2Rad) * WorldToClip(pw, leftCamera).x ;
        //Debug.Log(string.Format("x'':{0:F5}", xxxl));
        float tmp = ML[2, 0] * pw.x + ML[2, 1] * pw.y + ML[2, 2] * pw.z;
        //Debug.Log(string.Format("tmp'':{0:F5}", tmp));
        float ml23 = -xxl / xxxl - tmp;



        float xxr = MR[0, 0] * pw.x + MR[0, 1] * pw.y + MR[0, 2] * pw.z + MR[0, 3];
        float xxxr = Mathf.Tan(30 * Mathf.Deg2Rad) * WorldToClip(pw, rightCamera).x;
        float mr23 = -xxr / xxxr - (MR[2, 0] * pw.x + MR[2, 1] * pw.y + MR[2, 2] * pw.z);

        ML[2, 3] = ml23;
        MR[2, 3] = mr23;




        Debug.Log("ML:\n" + ML);
        Debug.Log("MR:\n" + MR);
    }

    private void OnGUI()
    {
        if (GUILayout.Button("Caculate"))
        {
            Caculate();
        }

        if (GUILayout.Button("Caculate1"))
        {
            Caculate1();
        }

        if (GUILayout.Button("TestUV"))
        {
            TestUV();
        }
    }


}
