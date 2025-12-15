// this file is just for internal testing, its not important for the engine
// but needed for compiling, you can just left it as is or use as
// example for using the engine, or even to test modifications on the engine.

#include <fireset/fireset.h>
#include <stdio.h>

int main(void){
    // inits engine
    if (!fsInit()) return 1;

    // creates window
    FsWindow window;
    window.width = 640;
    window.height = 480;
    window.name = "Example Game";
    fsCreateWindow(&window);

    FsVec2 vertices[3] = {
        {260, 270},
        {360, 270},
        {310, 170}
    };

    // main loop
    while (!fsWindowShouldClose(window)){
        fsClear(0, 0, 0);

        fsDrawTriangle(vertices, (FsColor){255, 128, 0});

        fsHandleWindow(&window);
    }

    // destroy window and closes engine
    fsDestroyWindow(&window);
    fsExit();
    return 0;
}