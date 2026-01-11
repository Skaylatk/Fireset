// Copyright (c) 2025-2026 Henrique Rodrigues Santos
// Licensed under the MIT License
// Github: https://github.com/saintsHr/Fireset

#include "fireset/window.h"
#include "fireset/render.h"
#include "fireset/input.h"
#include "fireset/fslog.h"

#include <stdbool.h>
#include <stdio.h>

static void fsFramebufferSizeCallback(GLFWwindow* window, int width, int height){
    (void)window;
    glViewport(0, 0, width, height);
    fsOrthoSet(width, height);
}

FsWindow fsWindowCreate(const char* name, FsVec2 size){
    FsWindow window = {
        .name = name,
        .width = size.x,
        .height = size.y
    };

    FsWindow nullwin = {0};

    // window hints
    glfwWindowHint(GLFW_DEPTH_BITS, 16);

    // creates window object and set context
    window.handle = glfwCreateWindow(window.width, window.height, window.name, NULL, NULL);
    if (!window.handle){
        glfwTerminate();
        fsLog(FS_FATAL, FS_WINDOW, "Failed to create window");
        return nullwin;
    }

    // centralizes the window
    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);
    int xPos = (mode->width  - window.width)  / 2;
    int yPos = (mode->height - window.height) / 2;
    glfwSetWindowPos(window.handle, xPos, yPos);

    // sets context and viewport
    glfwMakeContextCurrent(window.handle);
    glViewport(0, 0, window.width, window.height);

    // sets orthographic view
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    fsOrthoSet(window.width, window.height);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // enables depth testing
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    // binds resizing callback
    glfwSetFramebufferSizeCallback(window.handle, fsFramebufferSizeCallback);

    // returns window
    return window;
}

void fsWindowHandle(FsWindow* window){
    fsInputUpdate(window);
    glfwGetWindowSize(window->handle, &window->width, &window->height);
    glfwSwapBuffers(window->handle);
    glfwPollEvents();
}

void fsWindowDestroy(FsWindow* window){
    glfwDestroyWindow(window->handle);
}

bool fsWindowShouldClose(FsWindow* window){
    return glfwWindowShouldClose(window->handle);
}