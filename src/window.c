#include "fireset/window.h"

FsWindow* fsCreateWindow(FsWindow* window){
    // creates window object and set context
    window->handle = glfwCreateWindow(window->w, window->h, window->name, NULL, NULL);
    if (!window->handle){
        glfwTerminate();
        return window;
    }

    // sets context
    glfwMakeContextCurrent(window->handle);

    return window;
}