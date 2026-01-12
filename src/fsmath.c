// Copyright (c) 2025-2026 Henrique Rodrigues Santos
// Licensed under the MIT License
// Github: https://github.com/saintsHr/Fireset

#include "fireset/vector.h"
#include "fireset/color.h"

FsVec2 fsVecAdd(FsVec2 vec1, FsVec2 vec2){
    return (FsVec2){vec1.x + vec2.x, vec1.y + vec2.y,};
}

FsVec2 fsVecSub(FsVec2 vec1, FsVec2 vec2){
    return (FsVec2){vec1.x - vec2.x, vec1.y - vec2.y,};
}

FsVec2 fsVecMul(FsVec2 vec1, FsVec2 vec2){
    return (FsVec2){vec1.x * vec2.x, vec1.y * vec2.y,};
}

FsVec2 fsVecDiv(FsVec2 vec1, FsVec2 vec2){
    return (FsVec2){vec1.x / vec2.x, vec1.y / vec2.y,};
}

FsColor fsColorInvert(FsColor color){
    return (FsColor){255 - color.r, 255 - color.g, 255 - color.b};
}