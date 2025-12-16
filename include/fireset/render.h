#pragma once

#include <GL/gl.h>
#include "stdint.h"
#include "fireset/vertex.h"

/** 
 * @defgroup Render
 * @{
 */

typedef struct{
    uint8_t r, g, b;
}FsColor;

void fsDrawPixel(FsVec2 pos, FsColor color);
void fsDrawLine(FsVec2 p1, FsVec2 p2, FsColor color);
void fsDrawTriangle(const FsVec2* vertices, FsColor color);
void fsDrawQuad(const FsVec2* vertices, FsColor color);
void fsDrawCircle(FsVec2 center, int radius, int segments, FsColor color);
void fsDrawPolygon(const FsVec2* vertices, int count, FsColor color);
void fsSetOrtho(int width, int height);
void fsClear(FsColor color);

/** @} */