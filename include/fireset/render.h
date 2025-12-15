#pragma once

#include <GL/gl.h>
#include "stdint.h"
#include "fireset/vertex.h"

typedef struct{
    uint8_t r, g, b;
}FsColor;

void fsDrawTriangle(const FsVec2* vertices, FsColor color);
void fsDrawPixel(const FsVec2 pos, FsColor color);

void fsSetOrtho(int width, int height);
void fsClear(int red, int green, int blue);