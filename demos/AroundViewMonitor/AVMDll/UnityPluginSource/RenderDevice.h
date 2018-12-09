#pragma once

#include "Unity/IUnityGraphics.h"

#include <stddef.h>

#include "GLEW\glew.h"


#include <opencv2/opencv.hpp> //头文件
#include "../Render/CVTexture.h"
using namespace cv; //包含cv命名空间

struct IUnityInterfaces;

namespace cvBridge
{
	// Super-simple "graphics abstraction". This is nothing like how a proper platform abstraction layer would look like;
	// all this does is a base interface for whatever our plugin sample needs. Which is only "draw some triangles"
	// and "modify a texture" at this point.
	//
	// There are implementations of this base class for D3D9, D3D11, OpenGL etc.; see individual RenderAPI_* files.
	class RenderDevice
	{
	public:
		virtual ~RenderDevice() { }


		// Process general event like initialization, shutdown, device loss/reset etc.
		virtual void ProcessDeviceEvent(UnityGfxDeviceEventType type, IUnityInterfaces* interfaces) = 0;

		virtual void Texture2Mat(CVTexture *tex) = 0;
		virtual void Mat2Texture(CVTexture *tex) = 0;

	public:
		static RenderDevice *ins;
		// Create a graphics API implementation instance for the given API type.
		static RenderDevice* Create(UnityGfxRenderer apiType);
	};
}


