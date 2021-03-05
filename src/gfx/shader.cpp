//
// Created by 16182 on 7/16/2020.
//

#include "shader.hpp"
#include <vector>
#include <cstdio>
#include <unordered_map>
#include "../../src/io/io.hpp"

std::unordered_map<std::string, GLuint> shaderCache;

GLuint loadProgram(const char *vertexCode, const char *fragmentCode) {
    GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
    GLint Result = GL_FALSE;
    int InfoLogLength = 0;
    // Compile Vertex Shader
    glShaderSource(VertexShaderID, 1, &vertexCode , nullptr);
    glCompileShader(VertexShaderID);

    // Check Vertex Shader
    glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if ( InfoLogLength > 1 ){
        std::vector<char> VertexShaderErrorMessage(InfoLogLength+1);
        glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
        printf("Vertex: %s\n", &VertexShaderErrorMessage[0]);
    }



    // Compile Fragment Shader
    glShaderSource(FragmentShaderID, 1, &fragmentCode, nullptr);
    glCompileShader(FragmentShaderID);

    // Check Fragment Shader
    glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if ( InfoLogLength > 1 ){
        std::vector<char> FragmentShaderErrorMessage(InfoLogLength+1);
        glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
        printf("Fragment: %s\n", &FragmentShaderErrorMessage[0]);
    }



    // Link the program
    GLuint ProgramID = glCreateProgram();
    glAttachShader(ProgramID, VertexShaderID);
    glAttachShader(ProgramID, FragmentShaderID);
    glLinkProgram(ProgramID);

    // Check the program
    glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
    glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if ( InfoLogLength > 1 ){
        std::vector<char> ProgramErrorMessage(InfoLogLength+1);
        glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
        printf("Link: %s\n", &ProgramErrorMessage[0]);
    }

    auto a = glGetError();
    glDetachShader(ProgramID, VertexShaderID);
    glDetachShader(ProgramID, FragmentShaderID);

    glDeleteShader(VertexShaderID);
    glDeleteShader(FragmentShaderID);

    return ProgramID;
}

GLuint loadProgram(const std::string& vertexCode, const std::string& fragmentCode) {
    return loadProgram(vertexCode.c_str(), fragmentCode.c_str());
}

GLuint getProgram(const std::string &name) {
    auto id = shaderCache.find(name);
    if(id == shaderCache.end()){
        GLuint program = loadProgram(
                getFileContents("../res/v" + name + ".glsl"),
                getFileContents("../res/f" + name + ".glsl")
                );
        auto a = glGetError();
        shaderCache.insert({name, program});
        return program;
    } else {
        return id->second;
    }
}

void flushProgram(const std::string &name) {
    glDeleteProgram(shaderCache.at(name));
    shaderCache.erase(name);
}
