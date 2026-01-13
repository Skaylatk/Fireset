// Copyright (c) 2025-2026 Henrique Rodrigues Santos
// Licensed under the MIT License
// Github: https://github.com/saintsHr/Fireset

#include <fireset/fireset.h>

int main(void){
    fsInit(); // initializes the engine

    // creates a 800x600 window, with title "Example Game", not full-screen
    FsWindow window = fsWindowCreate("Example Game", (FsVec2){800, 600}, false);

    // creates a space with damping and without gravity
    FsSpace space = fsSpaceCreate((FsVec2){0.0f, 0.0f}, (FsVec2){0.95f, 0.95f});

    // creates player
    FsQuad player = {
        .angle = 0,                       // angle (in degrees)
        .color =  (FsColor){255, 127, 0}, // color (orange)
        .position = (FsVec2){400, 100},   // position (in pixels)
        .size = (FsVec2){100, 100},       // size (in pixels)
    };

    // creates player body
    FsBody playerBody = {
        .position = player.position, // position (in pixels)
        .size = player.size,         // size (in pixels)
        .type = FS_BODY_QUAD,        // body type
        .velocity = (FsVec2){0, 0}   // velocity
    };

    // adds playerBody to space
    fsSpaceAddBody(&space, &playerBody);

    // main window loop
    while (!fsWindowShouldClose(&window)){
        fsClear((FsColor){0, 0, 0});           // clears the window with a black color

        float speed = 10.0f;
        if (fsKeyDown(FS_KEY_W)) playerBody.velocity.y -= speed; // Up
        if (fsKeyDown(FS_KEY_A)) playerBody.velocity.x -= speed; // Left
        if (fsKeyDown(FS_KEY_S)) playerBody.velocity.y += speed; // Down
        if (fsKeyDown(FS_KEY_D)) playerBody.velocity.x += speed; // Right

        player.position = playerBody.position; // syncs body and shape position
        fsDrawQuad(&player, 1);                // draws the box in layer 1

        fsSpaceStep(&space, 60);               // steps space simulation 60 times a second
        fsWindowHandle(&window);               // handle window-related stuff
    }

    fsExit(); // shutdowns the engine
    return 0;
}