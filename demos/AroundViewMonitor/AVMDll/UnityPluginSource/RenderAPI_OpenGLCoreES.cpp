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

#include "../Render/Renderer_Triangle.h"
#include "../Render/Renderer_Quad.h"

class RenderAPI_OpenGLCoreES : public RenderDevice
{
public:
	RenderAPI_OpenGLCoreES(UnityGfxRenderer apiType);
	virtual ~RenderAPI_OpenGLCoreES() { }

	virtual void ProcessDeviceEvent(UnityGfxDeviceEventType type, IUnityInterfaces* interfaces);
	virtual void SetRenderTarget(GLuint target);
	virtual void DrawTestTriangle();
	virtual void DrawTestQuad();
	virtual void Blit(GLuint srcTexture);
	Renderer_Triangle* rendererTriange = nullptr;
	Renderer_Quad* rendererQuad = nullptr;

	GLuint FramebufferName = 0;

private:
	UnityGfxRenderer m_APIType;
	//GLuint m_VertexShader;
	//GLuint m_FragmentShader;
	//GLuint m_Program;
	//GLuint m_VertexArray;
	//GLuint m_VertexBuffer;
	//int m_UniformWorldMatrix;
	//int m_UniformProjMatrix;
};


RenderDevice* CreateRenderAPI_OpenGLCoreES(UnityGfxRenderer apiType)
{
	return new RenderAPI_OpenGLCoreES(apiType);
}


RenderAPI_OpenGLCoreES::RenderAPI_OpenGLCoreES(UnityGfxRenderer apiType)
	: m_APIType(apiType)
{
	glewExperimental = 1;
	glewInit();
	glGetError();
}


void RenderAPI_OpenGLCoreES::ProcessDeviceEvent(UnityGfxDeviceEventType type, IUnityInterfaces* interfaces)
{
	if (type == kUnityGfxDeviceEventInitialize)
	{
		//CreateResources();
	}
	else if (type == kUnityGfxDeviceEventShutdown)
	{
		//@TODO: release resources
	}
}

void RenderAPI_OpenGLCoreES::SetRenderTarget(GLuint renderedTexture)
{
	
	if (0 == renderedTexture)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		return;
	}
	
	if (FramebufferName == 0)
	{
		glGenFramebuffers(1, &FramebufferName);
	}
	
	glViewport(0, 0, 512, 512);
	glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, renderedTexture, 0);

	// Always check that our framebuffer is ok
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		return ;

	int a = 0;
	int b = 0;

}

void RenderAPI_OpenGLCoreES::DrawTestTriangle()
{	
	if (rendererTriange == nullptr)
	{
		rendererTriange = new Renderer_Triangle();
	}

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.4f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	rendererTriange->Draw();

	glFlush();
}


void RenderAPI_OpenGLCoreES::DrawTestQuad()
{
	if (rendererQuad == nullptr)
	{
		rendererQuad = new Renderer_Quad();
	}

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.4f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	rendererQuad->Draw();

	glFlush();
}

void RenderAPI_OpenGLCoreES::Blit(GLuint srcTexture)
{
	if (rendererQuad == nullptr)
	{
		rendererQuad = new Renderer_Quad();
	}

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.4f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	rendererQuad->texture = srcTexture;
	rendererQuad->Draw();

	glFlush();
}

#endif // #if SUPPORT_OPENGL_UNIFIED
