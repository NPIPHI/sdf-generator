//
// Created by 16182 on 7/16/2020.
//

#include "init.hpp"

GLFWwindow *makeWindow(int width, int height) {
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow * window = glfwCreateWindow(width, height, "ECS", nullptr, nullptr);
    glfwMakeContextCurrent(window);
    glewExperimental = true;
    glewInit();
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(1, 1, 0.5, 1);
    glfwSwapBuffers(window);
    return window;
}
