#include "Renderer_Quad.h"
#include "shader.hpp"

const char *UnlitTexture_VertexShader = R"(
#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec4 xyuv;
out vec2 uv;

void main(){

    gl_Position.xyzw = vec4(xyuv.xy,0.0,1.0);
    uv = xyuv.zw;
}

)";

const char *UnlitTexture_FragmentShader = R"(
#version 330 core

in vec2 uv;
out vec3 color;
uniform sampler2D _BaseTex;

void main()
{
	color = texture( _BaseTex, uv ).rgb;
}
)";

Renderer_Quad::Renderer_Quad()
{
	//programID = LoadShaders("E:/githome/Explore-To-OpenCV/demos/AroundViewMonitor/AVMDll/Shaders/UnlitTexture.vertexshader",
	//	"E:/githome/Explore-To-OpenCV/demos/AroundViewMonitor/AVMDll/Shaders/UnlitTexture.fragmentshader");

	programID = LoadShadersBySource(UnlitTexture_VertexShader, UnlitTexture_FragmentShader);

	//static const GLfloat g_vertex_buffer_data[] = {
	//	-1.0f, -1.0f, 0.0f,
	//	 1.0f, -1.0f, 0.0f,
	//	 1.0f,  1.0f, 0.0f,

	//	 -1.0f, -1.0f, 0.0f,
	//	 1.0f,  1.0f, 0.0f,
	//	 -1.0f,  1.0f, 0.0f,
	//};

	static const GLfloat g_vertex_buffer_data[] = {
	-0.8f, -0.8f, 0.0f, 0.0f,
	 0.8f, -0.8f, 1.0f, 0.0f,
	 0.8f,  0.8f, 1.0f, 1.0f,

	 -0.8f, -0.8f, 0.0f, 0.0f,
	 0.8f,  0.8f, 1.0f, 1.0f,
	 -0.8f,  0.8f, 0.0f,1.0f,
	};
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
}


void Renderer_Quad::Draw()
{
	GLuint textureID = glGetUniformLocation(programID, "_BaseTex");
	// Use our shader
	glUseProgram(programID);
	
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	// Set our "myTextureSampler" sampler to use Texture Unit 0
	glUniform1i(textureID, 0);
	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		4,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);

	// Draw the triangle !
	glDrawArrays(GL_TRIANGLES, 0, 6); // 3 indices starting at 0 -> 1 triangle

	glDisableVertexAttribArray(0);
}