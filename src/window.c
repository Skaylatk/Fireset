#include "fireset/window.h"
#include "fireset/render.h"

#include <stdbool.h>

void fsFramebufferSizeCallback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
    fsSetOrtho(width, height);
}

FsWindow* fsCreateWindow(FsWindow* window){
    // creates window object and set context
    window->handle = glfwCreateWindow(window->width, window->height, window->name, NULL, NULL);
    if (!window->handle){
        glfwTerminate();
        return window;
    }

    // sets context and viewport
    glfwMakeContextCurrent(window->handle);
    glViewport(0, 0, window->width, window->height);

    // enables depth test for 3D
    glEnable(GL_DEPTH_TEST);

    // sets orthographic view
    fsSetOrtho(window->width, window->height);

    // binds resizing callback
    glfwSetFramebufferSizeCallback(window->handle, fsFramebufferSizeCallback);

    return window;
}

void fsHandleWindow(FsWindow* window){
    glfwGetWindowSize(window->handle, &window->width, &window->height);
    glfwSwapBuffers(window->handle);
    glfwPollEvents();
}