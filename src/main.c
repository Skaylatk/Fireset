// this file is just for internal testing, its not important for the engine
// but needed for compiling, you can just left it as is or use as
// example for using the engine, or even to test modifications on the engine.

#include <fireset/fireset.h>

int main(void){
    // inits engine
    if (!fsInit()) return 1;

    // creates window
    FsWindow window;
    window.width = 800;
    window.height = 600;
    window.name = "Example Game";
    fsCreateWindow(&window);

    // main loop
    while (!fsWindowShouldClose(window)){
        fsClear((FsColor){0, 0, 0});

        // render here

        fsHandleWindow(&window);
    }

    // destroy window and closes engine
    fsDestroyWindow(&window);
    fsExit();
    return 0;
}