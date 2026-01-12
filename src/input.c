// Copyright (c) 2025-2026 Henrique Rodrigues Santos
// Licensed under the MIT License
// Github: https://github.com/saintsHr/Fireset

#include "fireset/input.h"
#include "fireset/vector.h"

typedef struct{
    bool pressed;
    bool just_pressed;
    bool just_released;
}FsInputKeyState;

#define NUM_KEYS (GLFW_KEY_LAST + 1)
static FsInputKeyState keys[NUM_KEYS];

void fsInputUpdate(FsWindow* window){
    for (int k = 0; k < NUM_KEYS; k++){
        bool isDown = glfwGetKey(window->handle, k) == GLFW_PRESS;

        keys[k].just_pressed  = (!keys[k].pressed && isDown);
        keys[k].just_released = (keys[k].pressed && !isDown);
        keys[k].pressed       = isDown;
    }
}

bool fsKeyJustPressed(FsKey key){
    return keys[key].just_pressed;
}

bool fsKeyJustReleased(FsKey key){
    return keys[key].just_released;
}

bool fsKeyDown(FsKey key){
    return keys[key].pressed;
}

FsVec2 fsCursorGetPos(const FsWindow* window){
    double x, y;

    glfwGetCursorPos(window->handle, &x, &y);

    float fx = (float)x;
    float fy = (float)y;

    FsVec2 vec = (FsVec2){fx, fy};
    return vec;
}

bool fsMouseButtonDown(const FsWindow* window, FsMouseButton bt){
    if (bt == FS_LMB && glfwGetMouseButton(window->handle, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS){
        return true;
    }
    if (bt == FS_RMB && glfwGetMouseButton(window->handle, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS){
        return true;
    }
    if (bt == FS_MMB && glfwGetMouseButton(window->handle, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS){
        return true;
    }
    return false;
}

bool fsMouseButtonJustPressed(const FsWindow* window, FsMouseButton bt){
    static bool wasPressed = false;
    bool isPressed = fsMouseButtonDown(window, bt);
    bool justPressed = isPressed && !wasPressed;
    wasPressed = isPressed;
    return justPressed;
}

bool fsMouseButtonJustReleased(const FsWindow* window, FsMouseButton bt) {
    static bool wasPressed = false;
    bool isPressed = fsMouseButtonDown(window, bt);
    bool justReleased = !isPressed && wasPressed;
    wasPressed = isPressed;
    return justReleased;
}