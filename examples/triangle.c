// Copyright (c) 2025-2026 Henrique Rodrigues Santos
// Licensed under the MIT License
// Github: https://github.com/saintsHr/Fireset

#include <fireset/fireset.h>

int main(void){
    fsInit(); // initializes the engine

    // creates a 800x600 window, with title "Example Game", not full-screen
    FsWindow window = fsWindowCreate("Example Game", (FsVec2){800, 600}, false);

    // creates triangle
    FsTriangle triangle = {
        .angle = 0,                         // angle (in degrees)
        .color =  (FsColor){255, 127, 0},   // color (orange)
        .position = (FsVec2){400, 300},     // position (in pixels)
        .size = (FsVec2){100, 100},         // size (in pixels)
    };

    // main window loop
    while (!fsWindowShouldClose(&window)){
        fsClear((FsColor){0, 0, 0});  // clears the window with a black color

        fsDrawTriangle(&triangle, 1); // draws the triangle in layer 1

        fsWindowHandle(&window);      // handle window-related stuff
    }

    fsExit(); // shutdowns the engine
    return 0;
}