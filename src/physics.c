// Copyright (c) 2025-2026 Henrique Rodrigues Santos
// Licensed under the MIT License
// Github: https://github.com/saintsHr/Fireset

#include "fireset/physics.h"
#include "fireset/fslog.h"

FsSpace fsSpaceCreate(FsVec2 gravity, FsVec2 damping){
    FsSpace s = {
        .bodyCount = 0,
        .gravity = gravity,
        .damping = damping
    };

    for (int i = 0; i < PHYS_MAX_BODIES; i++){
        s.bodies[i] = NULL;
    }

    return s;
}

void fsSpaceAddBody(FsSpace* space, FsBody* body){
    if (space->bodyCount >= PHYS_MAX_BODIES){
        fsLog(FS_ERROR, FS_PHYSICS, "Cannot add body to space, limit (%d) exceeded.", PHYS_MAX_BODIES);
        return;
    }

    space->bodies[space->bodyCount] = body;
    space->bodyCount++;
}

void fsSpaceStep(FsSpace* space, float stepTime){
    static double acumulador = 0.0f;
    float interval = 1.0f / stepTime;

    acumulador += fsTimeGetDelta();

    int maxSteps = 4;
    int steps = 0;
    while (acumulador >= interval && steps < maxSteps){
        acumulador -= interval;
        steps++;

        for (int i = 0; i < space->bodyCount; i++){
            FsBody* body = space->bodies[i];
            if (!body) continue;

            // apply gravity
            body->velocity.x += space->gravity.x * interval;
            body->velocity.y += space->gravity.y * interval;

            // apply damping
            body->velocity.x *= space->damping.x;
            body->velocity.y *= space->damping.y;

            // apply velocity
            body->position.x += body->velocity.x * interval;
            body->position.y += body->velocity.y * interval;
        }
    }
}



bool fsIsQuadColiding(FsBody quad1, FsBody quad2){
    if (quad1.type != FS_BODY_QUAD || quad2.type != FS_BODY_QUAD) return false;

    if (
        quad1.position.x + quad1.size.x/2 < quad2.position.x - quad2.size.x/2 ||
        quad1.position.x - quad1.size.x/2 > quad2.position.x + quad2.size.x/2 ||
        quad1.position.y + quad1.size.y/2 < quad2.position.y - quad2.size.y/2 ||
        quad1.position.y - quad1.size.y/2 > quad2.position.y + quad2.size.y/2
    ) return false;
    
    return true;
}