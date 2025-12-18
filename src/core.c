// Copyright (c) 2025 Henrique Rodrigues Santos
// Licensed under the MIT License
// Repo: https://github.com/saintsHr/Fireset

#include "fireset/core.h"

bool fsInit(){
    if(!glfwInit()) return false;
    return true;
}

void fsExit(){
    glfwTerminate();
}