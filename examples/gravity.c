// Copyright (c) 2025-2026 Henrique Rodrigues Santos
// Licensed under the MIT License
// Github: https://github.com/saintsHr/Fireset

#include <fireset/fireset.h>

int main(void){
    fsInit(); // initializes the engine

    // creates a 800x600 window, with title "Example Game", not full-screen
    FsWindow window = fsWindowCreate("Example Game", (FsVec2){800, 600}, false);

    // creates a space with gravity and damping
    FsSpace space = fsSpaceCreate((FsVec2){0.0f, 400.0f}, (FsVec2){1.0f, 1.0f});

    // creates box
    FsQuad box = {
        .angle = 0,                         // angle (in degrees)
        .color =  (FsColor){255, 127, 0},   // color (orange)
        .position = (FsVec2){400, 100},     // position (in pixels)
        .size = (FsVec2){100, 100},         // size (in pixels)
    };

    // creates box body
    FsBody boxBody = {
        .position = box.position,           // position (in pixels)
        .size = box.size,                   // size (in pixels)
        .type = FS_BODY_QUAD,               // body type
        .velocity = (FsVec2){0, 0}          // velocity
    };

    // adds boxBody to space
    fsSpaceAddBody(&space, &boxBody);

    // main window loop
    while (!fsWindowShouldClose(&window)){
        fsClear((FsColor){0, 0, 0});     // clears the window with a black color

        box.position = boxBody.position; // syncs body and shape position
        fsDrawQuad(&box, 1);             // draws the box in layer 1

        fsSpaceStep(&space, 60);         // steps space simulation 60 times a second
        fsWindowHandle(&window);         // handle window-related stuff
    }

    fsExit(); // shutdowns the engine
    return 0;
}