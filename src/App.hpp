#pragma once

#include <vector>
#include <GL/glew.h>

class App {
public:
    App();
    App(App &) = delete;
    App(App &&) = delete;
    void render();

private:
    struct {
        GLuint blitProgram;
        GLuint rastorTexture;
        GLuint sdfTexture;
        GLuint vertexAttribArray;
        GLuint uvArray;
        GLuint positionArray;
    } shader;
};
