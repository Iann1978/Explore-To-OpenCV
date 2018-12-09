// Example low level rendering Unity plugin

#include "PlatformBase.h"
#include "RenderDevice.h"
#include "../Render/Texture.h"
#include <assert.h>
#include <math.h>
#include <vector>
#include "RenderDevice.h"

#include <opencv2/opencv.hpp> //头文件

using namespace cv; //包含cv命名空间

#include "../OpenCVProcess.h"

using namespace cvBridge;


static void UNITY_INTERFACE_API OnGraphicsDeviceEvent(UnityGfxDeviceEventType eventType);

static IUnityInterfaces* s_UnityInterfaces = NULL;
static IUnityGraphics* s_Graphics = NULL;
static UnityGfxRenderer s_DeviceType = kUnityGfxRendererNull;

extern "C" void	UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API UnityPluginLoad(IUnityInterfaces* unityInterfaces)
{
	s_UnityInterfaces = unityInterfaces;
	s_Graphics = s_UnityInterfaces->Get<IUnityGraphics>();
	s_Graphics->RegisterDeviceEventCallback(OnGraphicsDeviceEvent);
	memset(Texture::cvTextures, sizeof(Texture*) * 32, 0);
	// Run OnGraphicsDeviceEvent(initialize) manually on plugin load
	OnGraphicsDeviceEvent(kUnityGfxDeviceEventInitialize);
}

extern "C" void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API UnityPluginUnload()
{
	s_Graphics->UnregisterDeviceEventCallback(OnGraphicsDeviceEvent);
}




static void UNITY_INTERFACE_API OnGraphicsDeviceEvent(UnityGfxDeviceEventType eventType)
{
	// Create graphics API implementation upon initialization
	if (eventType == kUnityGfxDeviceEventInitialize)
	{
		assert(RenderDevice::ins == NULL);
		s_DeviceType = s_Graphics->GetRenderer();
		RenderDevice::ins = RenderDevice::Create(s_DeviceType);
	}

	// Let the implementation process the device related events
	if (RenderDevice::ins)
	{
		RenderDevice::ins->ProcessDeviceEvent(eventType, s_UnityInterfaces);
	}

	// Cleanup graphics API implementation upon shutdown
	if (eventType == kUnityGfxDeviceEventShutdown)
	{
		delete RenderDevice::ins;
		RenderDevice::ins = NULL;
		s_DeviceType = kUnityGfxRendererNull;
	}
}





//char *image = nullptr;

//GLuint tempTexture = 0;
//Mat** inputs = nullptr;
//Mat** outputs = nullptr;
static void UNITY_INTERFACE_API OnRenderEvent(int eventID)
{
	if (eventID == 1)
	{
		// Convert CVTexture to cv::Mat
		for (int i = 0; i < 32; i++)
		{
			Texture* texture = Texture::cvTextures[i];
			if (texture)
			{	
				RenderDevice::ins->Texture2Mat(texture);
			}
		}

		// Process cv::Mat
		OpenCVProcess opencvProcess;
		opencvProcess.Process(nullptr, nullptr);

		// Convert cv::Mat to CVTexture
		for (int i = 16; i < 32; i++)
		{
			if (Texture::cvTextures[i])
			{
				RenderDevice::ins->Mat2Texture(Texture::cvTextures[i]);
			}
		}

		// Release resources
		for (int i = 0; i < 32; i++)
		{
			if (Texture::cvTextures[i])
			{
				if (Texture::cvTextures[i]->mat)
				{
					delete Texture::cvTextures[i]->mat;
					Texture::cvTextures[i]->mat = nullptr;
				}
			}
		}
	}
	
	return;

}


// --------------------------------------------------------------------------
// GetRenderEventFunc, an example function we export which is used to get a rendering event callback function.

extern "C" UnityRenderingEvent UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API GetRenderEventFunc()
{
	return OnRenderEvent;
}

