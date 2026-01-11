// Copyright (c) 2025-2026 Henrique Rodrigues Santos
// Licensed under the MIT License
// Github: https://github.com/saintsHr/Fireset

#pragma once

#include "fireset/vertex.h"
#include "fireset/render.h"

typedef enum{
    FS_CHAR_A,
    FS_CHAR_B,
    FS_CHAR_C,
    FS_CHAR_D,
    FS_CHAR_E,
    FS_CHAR_F,
    FS_CHAR_G,
    FS_CHAR_H,
    FS_CHAR_I,
    FS_CHAR_J,
    FS_CHAR_K,
    FS_CHAR_L,
    FS_CHAR_M,
    FS_CHAR_N,
    FS_CHAR_O,
    FS_CHAR_P,
    FS_CHAR_Q,
    FS_CHAR_R,
    FS_CHAR_S,
    FS_CHAR_T,
    FS_CHAR_U,
    FS_CHAR_V,
    FS_CHAR_W,
    FS_CHAR_X,
    FS_CHAR_Y,
    FS_CHAR_Z,

    FS_CHAR_UNKNOWN
}FsChar;

FsChar fsMapChar(char c);
void fsDrawChar(FsVec2 position, int size, FsColor color, FsChar c);
void fsDrawString(FsVec2 position, int size, FsColor color, const char* string);