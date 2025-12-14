#pragma once

#include <GLFW/glfw3.h>

typedef struct{
    GLFWwindow* handle;
    int w;
    int h;
    char* name;
}FsWindow;

FsWindow* fsCreateWindow(FsWindow* window);