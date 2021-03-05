#pragma once

#include <GL/glew.h>
#include<string>

GLuint get_BMP(const std::string& file_name);

GLuint loadTexture(const void * data, int width, int height, GLenum filtering = GL_LINEAR);
