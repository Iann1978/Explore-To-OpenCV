#pragma once
#include "Render\Texture.h"
namespace cvBridge
{
	class OpenCVProcess
	{
	public:
		static int intValues[32];
		static Texture*	cvTextures[32];
	public:
		virtual void Process(Mat** inputs, Mat** outputs);

	};
}

