#pragma once

#include <GL/glew.h>
#include <string>

GLuint loadProgram(const char * vertexCode, const char * fragmentCode);
GLuint loadProgram(const std::string& vertexCode, const std::string& fragmentCode);
GLuint getProgram(const std::string& name);
void flushProgram(const std::string &name);