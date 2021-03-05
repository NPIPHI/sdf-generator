#include<GL/glew.h>
#include <memory>
#include "gfx/init.hpp"
#include "mainLoop.h"
#include "App.hpp"


GLFWwindow * window;
struct {
    double width;
    double height;
} windowInfo;
std::unique_ptr<App> app;

void mainLoop() {
    static int frame = 0;
    frame++;
    glfwPollEvents();
    if (glfwWindowShouldClose(window)) {
        exitMainLoop();
        return;
    }
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    app->render();
}

int main() {
    window = makeWindow(1024, 1024);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    windowInfo.width = 1024;
    windowInfo.height = 1024;
    app = std::make_unique<App>();
    setMainLoop(mainLoop, window);
}
