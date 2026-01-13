// Copyright (c) 2025-2026 Henrique Rodrigues Santos
// Licensed under the MIT License
// Github: https://github.com/saintsHr/Fireset

#include <fireset/fireset.h>

int main(void){
    fsInit(); // initializes the engine

    // creates a 800x600 window, with title "Example Game", not full-screen
    FsWindow window = fsWindowCreate("Example Game", (FsVec2){800, 600}, false);

    // creates player
    FsQuad player = {
        .angle = 0,                       // angle (in degrees)
        .color =  (FsColor){255, 127, 0}, // color (orange)
        .position = (FsVec2){400, 100},   // position (in pixels)
        .size = (FsVec2){100, 100},       // size (in pixels)
    };

    // main window loop
    while (!fsWindowShouldClose(&window)){
        fsClear((FsColor){0, 0, 0}); // clears the window with a black color

        float dt = fsTimeGetDelta(); // gets delta time

        float speed = 250.0f;
        if (fsKeyDown(FS_KEY_W)) player.position.y -= speed * dt; // Up
        if (fsKeyDown(FS_KEY_A)) player.position.x -= speed * dt; // Left
        if (fsKeyDown(FS_KEY_S)) player.position.y += speed * dt; // Down
        if (fsKeyDown(FS_KEY_D)) player.position.x += speed * dt; // Right

        fsDrawQuad(&player, 1);  // draws the box in layer 1

        fsWindowHandle(&window); // handle window-related stuff
    }

    fsExit(); // shutdowns the engine
    return 0;
}