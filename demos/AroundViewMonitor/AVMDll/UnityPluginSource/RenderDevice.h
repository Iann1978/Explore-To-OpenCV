#pragma once

#include "Unity/IUnityGraphics.h"

#include <stddef.h>

#include "GLEW\glew.h"

struct IUnityInterfaces;


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

	// Set render target for this device. 0 for draw unity screen.
	virtual void SetRenderTarget(GLuint target) = 0;

	// Used for test the plugin
	virtual void DrawTestTriangle() = 0;

	// Used for test the plugin
	virtual void DrawTestQuad() = 0;

	virtual void Blit(GLuint srcTexture) = 0;

	
public:
	static RenderDevice *ins;
	// Create a graphics API implementation instance for the given API type.
	static RenderDevice* Create(UnityGfxRenderer apiType);
};



