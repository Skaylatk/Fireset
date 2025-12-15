#include "fireset/window.h"

#include <stdbool.h>

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

    return window;
}

void fsHandleWindow(FsWindow* window){
    glfwSwapBuffers(window->handle);
    glfwPollEvents();
}