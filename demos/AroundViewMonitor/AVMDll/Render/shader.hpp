#ifndef SHADER_HPP
#define SHADER_HPP

GLuint LoadShaders(const char * vertex_file_path,const char * fragment_file_path);
GLuint LoadShadersBySource(const char * vertex_shader_source, const char * fragment_shader_source);
#endif
