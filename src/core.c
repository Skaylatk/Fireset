#include "fireset/core.h"

bool fsInit(){
    if(!glfwInit()) return false;
    return true;
}

void fsExit(){
    glfwTerminate();
}