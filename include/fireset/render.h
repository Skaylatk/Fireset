#pragma once

#include <GL/gl.h>
#include "fireset/vertex.h"

void fsDrawTriangle(const FsVec2* vertices);
void fsSetOrtho(int width, int height);
void fsClear(int red, int green, int blue);