#define EXPORT_API __declspec(dllexport)
#include <Eigen/Dense>
using namespace Eigen;
extern "C" {
	EXPORT_API float getTrace() {
		MatrixXf m = MatrixXf::Random(4, 4);
		//return m.trace();
		return 0.678;
	}

	/*
	M*x=N;M(m*n),N(m*1)
	*/
	EXPORT_API bool cal_line_equation(float *x, int m, int n, float *M, float *N)
	{
		MatrixXf MM = MatrixXf::Random(m, n);
		MatrixXf NN = MatrixXf::Random(m, 1);

		for (int r = 0; r < m; r++)
		{
			NN(r, 0) = N[r];
			for (int c = 0; c < n; c++)
			{
				MM(r, c) = M[r*n + c];
			}
		}
		MatrixXf XX = (MM.transpose() * MM).inverse() * MM.transpose() * NN;
		for (int i = 0; i < n; i++)
		{
			x[i] = XX(i, 0);
		}



		return true;
	}
}