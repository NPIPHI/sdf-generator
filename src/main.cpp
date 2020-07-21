#include<GL/glew.h>
#include <memory>
#include "gfx/init.hpp"
#include "src/io/io.hpp"
#include "gfx/shader.hpp"
#include "mainLoop.h"
#include "game/game.h"
#include <chrono>
#include <iostream>


GLFWwindow * window;
struct {
    double width;
    double height;
} windowInfo;
std::unique_ptr<game> mainGame;

void mainLoop() {
    static int frame = 0;
    frame++;
    glfwPollEvents();
    if (glfwWindowShouldClose(window)) {
        exitMainLoop();
        return;
    }
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if(glfwGetKey(window, GLFW_KEY_R)){
        mainGame->update();
    }
    auto start = std::chrono::high_resolution_clock::now();
    for(int i = 0; i < 1; i++){
        mainGame->render();
        glFinish();
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << (end - start) / std::chrono::microseconds(1) << std::endl;
}

int main() {
    window = makeWindow(1024, 1024);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    windowInfo.width = 1024;
    windowInfo.height = 1024;
    mainGame = std::make_unique<game>();
    setMainLoop(mainLoop, window);
}
