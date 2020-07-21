//
// Created by 16182 on 7/17/2020.
//

#include <src/gfx/texture.hpp>
#include <src/gfx/bufferObject.h>
#include "sdf.h"
#include <src/gfx/shader.hpp>
#include <glm/glm.hpp>

bool initilized = false;

struct {
    GLuint outlineProgram;
    GLuint fillProgram;
    GLuint sdfProgram;
    GLuint vertexAttribArray;
    GLuint positionArray;
    GLuint uvArray;
    GLuint rasterTexture;
    GLuint rasterTexLocation;
    GLuint closestTexLocation;
    GLuint textureLocation;
    GLuint sdfRadiusLocation;
    frameBufferObject frameA;
    frameBufferObject frameB;
    frameBufferObject frameOut;
    GLuint jumpLocation;
} shader;

void init();
GLuint render(GLuint source_texture, GLuint dest_texture, int sdfRadius, int width, int height);

GLuint  gen_SDF(GLuint source_texture, GLuint dest_texture, int width, int height) {
    if(!initilized){
        init();
    }

    if(dest_texture == 0){
        glGenTextures(1, &dest_texture);
        glBindTexture(GL_TEXTURE_2D, dest_texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
    }

    return render(source_texture, dest_texture, 256, width, height);
}

GLuint render(GLuint source_texture, GLuint dest_texture, int sdfRadius, int width, int height) {
    if(width != shader.frameA.width || height != shader.frameA.height){
        shader.frameA.resize(width, height);
        shader.frameB.resize(width, height);
    }
    shader.frameOut.setTexture(dest_texture, width, height);

    bufferObject<glm::vec2, glm::vec2> buf;
    buf.push_back<0>(glm::vec2{-1, -1});
    buf.push_back<0>(glm::vec2{-1, 3});
    buf.push_back<0>(glm::vec2{3, -1});
    buf.push_back<1>(glm::vec2{0, 0});
    buf.push_back<1>(glm::vec2{0, 2});
    buf.push_back<1>(glm::vec2{2, 0});

    glDisable(GL_BLEND);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(shader.vertexAttribArray);
    buf.bufferData(shader.positionArray, shader.uvArray);

    shader.frameA.bind();
    glUseProgram(shader.outlineProgram);
    glBindTexture(GL_TEXTURE_2D, source_texture);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    int pow2 = 0;
    while(std::pow(2, pow2) < sdfRadius){
        pow2++;
    }

    frameBufferObject * fbo1 = &shader.frameA;
    frameBufferObject * fbo2 = &shader.frameB;
    glUseProgram(shader.fillProgram);

    for(int i = pow2; i >= 0; i--){
        fbo2->bind();
        glBindTexture(GL_TEXTURE_2D, fbo1->texture);
        glUniform1i(shader.jumpLocation, std::pow(2, i));
        glDrawArrays(GL_TRIANGLES, 0, 3);
        std::swap(fbo1, fbo2);
    }

    shader.frameOut.bind();
    glUseProgram(shader.sdfProgram);
    glBindTexture(GL_TEXTURE_2D, fbo1->texture);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, shader.rasterTexture);
    glUniform1f(shader.sdfRadiusLocation, float(fbo2->width)/float(sdfRadius));
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    return shader.frameOut.releaseTexture();
}

void init() {
    shader.rasterTexture = get_BMP("../res/font.bmp");
    shader.outlineProgram = getProgram("GenOutline");
    shader.fillProgram = getProgram("Fill");
    shader.sdfProgram = getProgram("GenSDF");
    shader.textureLocation = glGetUniformLocation(shader.outlineProgram, "tex");
    shader.rasterTexLocation = glGetUniformLocation(shader.sdfProgram, "interiorMask");
    shader.closestTexLocation = glGetUniformLocation(shader.sdfProgram, "closestTexture");
    shader.jumpLocation = glGetUniformLocation(shader.fillProgram, "jump");
    shader.sdfRadiusLocation = glGetUniformLocation(shader.sdfProgram, "sdfRadius");

    shader.frameA = frameBufferObject{1, 1, GL_RGBA16F};
    shader.frameB = frameBufferObject{1, 1, GL_RGBA16F};
    shader.frameOut = frameBufferObject{1, 1, GL_RGBA};

    glGenVertexArrays(1, &shader.vertexAttribArray);
    glBindVertexArray(shader.vertexAttribArray);

    GLuint positionLocator = glGetAttribLocation(shader.outlineProgram, "position");
    glGenBuffers(1, &shader.positionArray);
    glBindBuffer(GL_ARRAY_BUFFER, shader.positionArray);
    glEnableVertexAttribArray(positionLocator);
    glVertexAttribPointer(positionLocator, 2, GL_FLOAT, GL_FALSE, 0, 0);

    GLuint uvLocator = glGetAttribLocation(shader.outlineProgram, "uv");
    glGenBuffers(1, &shader.uvArray);
    glBindBuffer(GL_ARRAY_BUFFER, shader.uvArray);
    glEnableVertexAttribArray(uvLocator);
    glVertexAttribPointer(uvLocator, 2, GL_FLOAT, GL_FALSE, 0, 0);

    initilized = true;
}
