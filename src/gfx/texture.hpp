#pragma once

#include <src/io/io.hpp>
#include <GL/glew.h>

GLuint get_BMP(const std::string& file_name);

GLuint loadTexture(const void * data, int width, int height, GLenum filtering = GL_LINEAR);
