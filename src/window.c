// Copyright (c) 2025 Henrique Rodrigues Santos
// Licensed under the MIT License
// Repo: https://github.com/saintsHr/Fireset

#include "fireset/window.h"
#include "fireset/render.h"
#include "fireset/input.h"

#include <stdbool.h>
#include <stdio.h>

static void fsFramebufferSizeCallback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
    fsOrthoSet(width, height);
}

FsWindow* fsWindowCreate(FsWindow* window){
    // window hints
    glfwWindowHint(GLFW_DEPTH_BITS, 24);

    // creates window object and set context
    window->handle = glfwCreateWindow(window->width, window->height, window->name, NULL, NULL);
    if (!window->handle){
        glfwTerminate();
        return window;
    }

    // sets context and viewport
    glfwMakeContextCurrent(window->handle);
    glViewport(0, 0, window->width, window->height);

    // sets orthographic view
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    fsOrthoSet(window->width, window->height);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // enables depth testing
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    // binds resizing callback
    glfwSetFramebufferSizeCallback(window->handle, fsFramebufferSizeCallback);

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