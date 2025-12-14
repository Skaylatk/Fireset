#include "fireset/core.h"
#include "fireset/window.h"

#include <GLFW/glfw3.h>

void fsMainLoop(FsWindow* window, void (*f)(void)){
    while (!glfwWindowShouldClose(window->handle)){
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        f();

        glfwSwapBuffers(window->handle);
        glfwPollEvents();
    }
}