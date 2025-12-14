#include <fireset/fireset.h>

#include <GLFW/glfw3.h>

int main(void){
    // inits glfw
    if (!glfwInit()) return 1;

    // creates window
    FsWindow window;
    window.w = 640;
    window.h = 480;
    window.name = "Example Game";

    fsCreateWindow(&window);

    // main loop
    while (!glfwWindowShouldClose(window.handle)){
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // render here

        glfwSwapBuffers(window.handle);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}