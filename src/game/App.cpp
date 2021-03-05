//
// Created by 16182 on 7/17/2020.
//

#include "../gfx/texture.hpp"
#include "../gfx/bufferObject.h"
#include "App.h"
#include "../gfx/shader.hpp"
#include "../sdf/sdf.h"


void App::render() {
    bufferObject<glm::vec2, glm::vec2> buf;
    buf.push_back<0>(glm::vec2{-1, -1});
    buf.push_back<0>(glm::vec2{-1, 3});
    buf.push_back<0>(glm::vec2{3, -1});
    buf.push_back<1>(glm::vec2{0, 0});
    buf.push_back<1>(glm::vec2{0, 2});
    buf.push_back<1>(glm::vec2{2, 0});

    shader.sdfTexture = gen_SDF(shader.rastorTexture, shader.sdfTexture, 1024, 1024);

    glBindVertexArray(shader.vertexAttribArray);
    buf.bufferData(shader.positionArray, shader.uvArray);

    glEnable(GL_BLEND);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glUseProgram(shader.blitProgram);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, shader.sdfTexture);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

App::App() {
    shader.blitProgram = getProgram("Blit");
    shader.rastorTexture = get_BMP("../res/font.bmp");
    shader.sdfTexture = gen_SDF(shader.rastorTexture, 0, 1024, 1024);

    glGenVertexArrays(1, &shader.vertexAttribArray);
    glBindVertexArray(shader.vertexAttribArray);

    GLuint positionLocator = glGetAttribLocation(shader.blitProgram, "position");
    glGenBuffers(1, &shader.positionArray);
    glBindBuffer(GL_ARRAY_BUFFER, shader.positionArray);
    glEnableVertexAttribArray(positionLocator);
    glVertexAttribPointer(positionLocator, 2, GL_FLOAT, GL_FALSE, 0, 0);

    GLuint uvLocator = glGetAttribLocation(shader.blitProgram, "uv");
    glGenBuffers(1, &shader.uvArray);
    glBindBuffer(GL_ARRAY_BUFFER, shader.uvArray);
    glEnableVertexAttribArray(uvLocator);
    glVertexAttribPointer(uvLocator, 2, GL_FLOAT, GL_FALSE, 0, 0);
}