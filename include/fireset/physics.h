// Copyright (c) 2025-2026 Henrique Rodrigues Santos
// Licensed under the MIT License
// Github: https://github.com/saintsHr/Fireset

#pragma once

#include "fireset/render.h"
#include "fireset/settings.h"

#include <stdbool.h>

typedef enum{
    FS_BODY_QUAD,
    FS_BODY_CIRCLE
}FsBodyType;

typedef struct{
    FsBodyType type;
    FsVec2 position;
    FsVec2 size;
    FsVec2 velocity;
}FsBody;

typedef struct{
    FsVec2 gravity;
    FsVec2 damping;

    int bodyCount;
    FsBody* bodies[PHYS_MAX_BODIES];
}FsSpace;

FsSpace fsSpaceCreate(FsVec2 gravity, FsVec2 damping);
void fsSpaceAddBody(FsSpace* space, FsBody* body);
void fsSpaceStep(FsSpace* space, float stepTime);
bool fsIsQuadColiding(FsBody quad1, FsBody quad2);