// Example low level rendering Unity plugin

#include "PlatformBase.h"
#include "RenderDevice.h"
#include "../Render/Texture.h"
#include <assert.h>
#include <math.h>
#include <vector>


#include <opencv2/opencv.hpp> //头文件

using namespace cv; //包含cv命名空间

#include "../OpenCVProcess.h"


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





char *image = nullptr;

//GLuint tempTexture = 0;
//Mat** inputs = nullptr;
//Mat** outputs = nullptr;
static void UNITY_INTERFACE_API OnRenderEvent(int eventID)
{
	if (eventID == 1)
	{
		
		GLenum err;
		if (!image)
		{
			image = new char[2048 * 2048 * 4];
			//glGenTextures(1, &tempTexture);
			err = glGetError();
		}



		//if (!outputs)
		//{
		//	outputs = new Mat*[16];
		//	memset(outputs, sizeof(Mat*) * 16, 0);
		//}


		for (int i = 0; i < 16; i++)
		{
			if (Texture::cvTextures[i])
			{
				Texture* texture = Texture::cvTextures[i];
				
				glBindTexture(GL_TEXTURE_2D, texture->texture);
				err = glGetError();
				glGetTexImage(GL_TEXTURE_2D, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
				err = glGetError();
				Texture::cvTextures[i]->mat = new Mat(texture->width, texture->height, CV_8UC3, image);
			}
		}

		for (int i = 16; i < 32; i++)
		{
			if (Texture::cvTextures[i])
			{
				Texture::cvTextures[i]->mat = new Mat();
			}
		}
	
		//
		//glBindTexture(GL_TEXTURE_2D, Texture::cvTextures[0]->texture);
		//err = glGetError();
		//glGetTexImage(GL_TEXTURE_2D, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		//err = glGetError();



		
		//outputs[0] = new Mat();
		
		OpenCVProcess opencvProcess;
		opencvProcess.Process(nullptr, nullptr);

		//glBindTexture(GL_TEXTURE_2D, Texture::cvTextures[16]->texture);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		//glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB8, 512, 256, 0, GL_BGRA, GL_UNSIGNED_BYTE, image);

		//glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 512, 256, GL_RGB, GL_UNSIGNED_BYTE, image);
		//glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 512, 512, GL_RGB, GL_UNSIGNED_BYTE, outputs[0]->ptr());

		for (int i = 16; i < 32; i++)
		{
			if (Texture::cvTextures[i])
			{
				glBindTexture(GL_TEXTURE_2D, Texture::cvTextures[i]->texture);
				glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 512, 512, GL_RGB, GL_UNSIGNED_BYTE, Texture::cvTextures[i]->mat->ptr());
			}
		}


		err = glGetError();


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

		//delete inputs[0];
		//inputs[0] = nullptr;
		//delete outputs[0];
		//outputs[0] = nullptr;
		//Mat sourceImage = Mat(256, 512, CV_8UC3, image);
		//Mat greyImage;

		//cvtColor(sourceImage, greyImage, COLOR_RGB2GRAY);

		//Matrix = Mat(texture_height, texture_width, CV_8UC3, texture_bytes);


		//glGetTexImage(Texture::cvTextures[1]->texture, 0, GL_RGBA, GL_SRGB8_ALPHA8, image);

		//RenderDevice::ins->SetRenderTarget(Texture::cvTextures[16]->texture);
		////RenderDevice::ins->DrawTestTriangle();
		////RenderDevice::ins->DrawTestQuad();
		//RenderDevice::ins->Blit(tempTexture);
		//RenderDevice::ins->SetRenderTarget(0);
	}
	
	return;

}


// --------------------------------------------------------------------------
// GetRenderEventFunc, an example function we export which is used to get a rendering event callback function.

extern "C" UnityRenderingEvent UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API GetRenderEventFunc()
{
	return OnRenderEvent;
}

