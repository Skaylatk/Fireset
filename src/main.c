#include <fireset/fireset.h>

int main(void){
    // inits engine
    if (!fsInit()) return 1;

    // creates window
    FsWindow window;
    window.width = 640;
    window.height = 480;
    window.name = "Example Game";
    fsCreateWindow(&window);

    // tringle vertices
    FsVec2f vertices[3] = {
        {-0.5f, -0.5f },
        { 0.5f, -0.5f },
        { 0.0f,  0.5f }
    };

    // main loop
    while (!fsWindowShouldClose(window)){
        fsClear(0, 0, 0);

        fsDrawTriangle(vertices);

        fsHandleWindow(&window);
    }

    // destroy window and closes engine
    fsDestroyWindow(&window);
    fsExit();
    return 0;
}