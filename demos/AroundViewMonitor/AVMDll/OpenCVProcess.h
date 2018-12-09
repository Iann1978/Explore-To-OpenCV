#pragma once
#include "Render\CVTexture.h"
namespace cvBridge
{
	class OpenCVProcess
	{
	public:
		static int intValues[32];
		static CVTexture*	cvTextures[32];
	public:
		virtual void Process(Mat** inputs, Mat** outputs);

	};
}

