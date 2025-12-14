#include <fireset/fireset.h>
#include <GLFW/glfw3.h>

void loop(){
    
}

int main(void){
    // inits engine
    if (!fsInit()) return 1;

    // creates window
    FsWindow window;
    window.w = 640;
    window.h = 480;
    window.name = "Example Game";
    fsCreateWindow(&window);

    // main loop
    fsMainLoop(&window, loop);

    // destroy window and closes engine
    fsDestroyWindow(&window);
    fsExit();
    return 0;
}