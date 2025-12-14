#pragma once

#include "fireset/window.h"

#include <GLFW/glfw3.h>
#include <stdbool.h>

static inline bool fsInit(){
    if(!glfwInit()) return false;
    return true;
}

static inline void fsExit(){
    glfwTerminate();
}

void fsMainLoop(FsWindow* window, void (*f)(void));