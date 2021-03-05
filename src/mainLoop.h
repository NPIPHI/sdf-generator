#pragma once

typedef void(*callback_function)();

#include <GLFW/glfw3.h>
#ifdef __EMSCRIPTEN__
#include<emscripten.h>
void setMainLoop(callback_function callback, GLFWwindow * window){
    emscripten_set_main_loop(callback, 0, false);
}

void exitMainLoop(){
    emscripten_cancel_main_loop();
}

#else

#include<thread>

bool inLoop = false;
void setMainLoop(callback_function callback, GLFWwindow * window) {
    inLoop = true;
    glfwSwapInterval(1);
    while (inLoop){
        callback();
        glfwSwapBuffers(window);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void exitMainLoop(){
    inLoop = false;
}
#endif