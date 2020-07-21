#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <GL/glew.h>
#include "entity.h"

class game {
public:
    game();
    game(game &) = delete;
    game(game &&) = delete;
    void render();
    void update();
    void click(float x, float y);

private:
    std::vector<entity> entites;
    struct {
        GLuint blitProgram;
        GLuint rastorTexture;
        GLuint sdfTexture;
        GLuint vertexAttribArray;
        GLuint uvArray;
        GLuint positionArray;
    } shader;
};
