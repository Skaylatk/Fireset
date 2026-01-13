// Copyright (c) 2025-2026 Henrique Rodrigues Santos
// Licensed under the MIT License
// Github: https://github.com/saintsHr/Fireset

#include <fireset/fireset.h>

int main(void){
    fsInit(); // initializes the engine

    // creates a 800x600 window, with title "Example Game", not full-screen
    FsWindow window = fsWindowCreate("Example Game", (FsVec2){800, 600}, false);

    // main window loop
    while (!fsWindowShouldClose(&window)){
        fsClear((FsColor){0, 0, 0}); // clears the window with a black color
        fsWindowHandle(&window);     // handle window-related stuff
    }

    fsExit(); // shutdowns the engine
    return 0;
}