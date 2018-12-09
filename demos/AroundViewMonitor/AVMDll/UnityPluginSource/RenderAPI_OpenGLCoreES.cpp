#include "RenderDevice.h"
#include "PlatformBase.h"

// OpenGL Core profile (desktop) or OpenGL ES (mobile) implementation of RenderAPI.
// Supports several flavors: Core, ES2, ES3


#if SUPPORT_OPENGL_UNIFIED


#include <assert.h>
#if UNITY_IPHONE
#	include <OpenGLES/ES2/gl.h>
#elif UNITY_ANDROID || UNITY_WEBGL
#	include <GLES2/gl2.h>
#else
#	include "GLEW/glew.h"
#endif



namespace cvBridge
{
	class RenderDevice_OpenGLCoreES : public RenderDevice
	{
	public:
		RenderDevice_OpenGLCoreES(UnityGfxRenderer apiType);
		virtual ~RenderDevice_OpenGLCoreES() { }

		virtual void ProcessDeviceEvent(UnityGfxDeviceEventType type, IUnityInterfaces* interfaces);

		virtual void Texture2Mat(Texture* tex);
		virtual void Mat2Texture(Texture *tex);


	private:
		UnityGfxRenderer m_APIType;
	};




	RenderDevice_OpenGLCoreES::RenderDevice_OpenGLCoreES(UnityGfxRenderer apiType)
		: m_APIType(apiType)
	{
		glewExperimental = 1;
		glewInit();
		glGetError();
	}


	void RenderDevice_OpenGLCoreES::ProcessDeviceEvent(UnityGfxDeviceEventType type, IUnityInterfaces* interfaces)
	{
		if (type == kUnityGfxDeviceEventInitialize)
		{
			//@TODO: initialize resources
		}
		else if (type == kUnityGfxDeviceEventShutdown)
		{
			//@TODO: release resources
		}
	}

	void RenderDevice_OpenGLCoreES::Texture2Mat(Texture* tex)
	{
		glBindTexture(GL_TEXTURE_2D, tex->texture);
		glGetTexImage(GL_TEXTURE_2D, 0, GL_RGB, GL_UNSIGNED_BYTE, tex->image);
		tex->mat = new Mat(tex->height, tex->width, CV_8UC3, tex->image);
	}

	void RenderDevice_OpenGLCoreES::Mat2Texture(Texture *tex)
	{
		glBindTexture(GL_TEXTURE_2D, tex->texture);
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, tex->width, tex->height, GL_RGB, GL_UNSIGNED_BYTE, tex->mat->ptr());
	}
}


cvBridge::RenderDevice* CreateRenderAPI_OpenGLCoreES(UnityGfxRenderer apiType)
{
	return new cvBridge::RenderDevice_OpenGLCoreES(apiType);
}
#endif // #if SUPPORT_OPENGL_UNIFIED
