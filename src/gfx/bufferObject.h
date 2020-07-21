#pragma once

#include <vector>
#include <GL/glew.h>

template<typename buf1, typename... bufN>
struct bufferObject{
    bufferObject() = default;
    bufferObject(bufferObject&) = delete;
    bufferObject(bufferObject&&) = delete;

    void bufferData(GLuint glBuffer, GLuint glBuffers...){
        glBindBuffer(GL_ARRAY_BUFFER, glBuffer);
        glBufferData(GL_ARRAY_BUFFER, byte_size<0>(), data<0>(), GL_DYNAMIC_DRAW);
        subBuffers.bufferData(glBuffers);
    }

    size_t vertex_count() const{
        return _data.size();
    }
    template<int index>
    void clear(){
        if constexpr(index == 0){
            _data.clear();
        } else {
            subBuffers.template clear<index - 1>();
        }
    }
    template<int index>
    size_t byte_size() const{
        if constexpr (index == 0){
            return _data.size() * sizeof(buf1);
        } else {
            return byte_size<index - 1>();
        }
    }
    template<int index>
    const void * data() const{
        if constexpr (index == 0) {
            return _data.data();
        } else {
            return data<index - 1>();
        }
    }
    template<int index>
    auto & get(){
        if constexpr (index == 0){
            return _data;
        } else {
            return subBuffers.template get<index - 1>();
        }
    }
    template<int index, typename T>
    void push_back(T val){
        if constexpr (index == 0){
            _data.push_back(val);
        } else {
            subBuffers.template push_back<index - 1>(val);
        }
    }
private:
    std::vector<buf1> _data;
    bufferObject<bufN...> subBuffers;
};

template<typename buf1>
struct bufferObject<buf1>{
    bufferObject() = default;
    bufferObject(bufferObject&) = delete;
    bufferObject(bufferObject&&) = delete;

    void bufferData(GLuint glBuffer) {
        glBindBuffer(GL_ARRAY_BUFFER, glBuffer);
        glBufferData(GL_ARRAY_BUFFER, byte_size<0>(), data<0>(), GL_DYNAMIC_DRAW);
    }
    size_t vertex_count() const{
        return _data.size();
    }
    template<int index>
    void clear(){
        static_assert(index == 0, "oob index");
        _data.clear();
    }
    template<int index>
    auto & get(){
        static_assert(index == 0, "get index out of range");
        return _data;
    }
    template<int index>
    const void * data() const{
        static_assert(index == 0, "data index out of range");
        return _data.data();
    }
    template<int index, typename T>
    void push_back(T val){
        static_assert(index == 0, "push_back index out of range");
        return _data.push_back(val);
    }
    template<int index>
    size_t byte_size() const{
        static_assert(index == 0, "byte_size index out of range");
        return _data.size() * sizeof(buf1);
    }
private:
    std::vector<buf1> _data;
};

struct frameBufferObject{
    GLuint frameBuffer;
    GLuint texture;
    GLenum drawBuffer;
    GLenum format;
    int width, height;
    frameBufferObject() = default;
    void clear(){
        if(frameBuffer!=0){
            glDeleteFramebuffers(1, &frameBuffer);
        }
        if(texture!=0){
            glDeleteTextures(1, &texture);
        }
    }
    void setTexture(GLuint texture, int width, int height){
        this->width = width;
        this->height = height;
        this->texture = texture;
        glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, texture, 0);
    }
    void resize(int width, int height){
        this->width = width;
        this->height = height;
        glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
        glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, texture, 0);
    }
    frameBufferObject(int width, int height, GLenum format): width(width), height(height), format(format){
        glGenFramebuffers(1, &frameBuffer);
        glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, texture, 0);


        drawBuffer = GL_COLOR_ATTACHMENT0;
        glDrawBuffers(1, &drawBuffer);

        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
            throw std::exception();
        }

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
    GLuint releaseTexture(){
        GLuint ret = texture;
        texture = 0;
        return ret;
    }
    void bind() const{
        glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
        glViewport(0, 0, width, height);
    }
};