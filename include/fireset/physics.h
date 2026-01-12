// Copyright (c) 2025-2026 Henrique Rodrigues Santos
// Licensed under the MIT License
// Github: https://github.com/saintsHr/Fireset

#pragma once

#include "fireset/render.h"
#include "fireset/settings.h"

#include <stdbool.h>

/**
 * @defgroup Physics Physics
 * @brief Simple 2D physics simulation module.
 * @{
 */

/**
 * @brief Physics body types.
 *
 * Defines the shape and behavior of a physics body.
 */
typedef enum {
    FS_BODY_QUAD,   /**< Circle Body */
    FS_BODY_CIRCLE  /**< Axis-aligned rectangle body */
} FsBodyType;

/**
 * @brief Physics body.
 *
 * Represents a physical object inside a physics space.
 * Stores position, velocity, size and body type.
 */
typedef struct {
    FsBodyType type;   /**< Body shape/type */

    FsVec2 position;   /**< World position (center-based) */
    FsVec2 velocity;   /**< Linear velocity */
    FsVec2 size;       /**< Size of the body (width, height) */
} FsBody;

/**
 * @brief Physics simulation space.
 *
 * A space contains and updates multiple physics bodies.
 * Gravity and damping are applied uniformly to all bodies.
 */
typedef struct {
    FsBody* bodies[PHYS_MAX_BODIES]; /**< Array of body pointers */
    int bodyCount;                   /**< Number of active bodies */

    FsVec2 gravity;                  /**< Gravity vector (units/s²) */
    FsVec2 damping;                  /**< Velocity damping factor */
} FsSpace;

/**
 * @brief Creates a physics simulation space.
 *
 * Initializes a physics space with gravity and damping parameters.
 * The space starts empty, with no bodies attached.
 *
 * @param gravity Gravity applied to all bodies.
 * @param damping Velocity damping applied every simulation step.
 *
 * @return Initialized physics space.
 */
FsSpace fsSpaceCreate(FsVec2 gravity, FsVec2 damping);

/**
 * @brief Adds a body to a physics space.
 *
 * Inserts a body so it will be updated during simulation.
 * If the body limit is exceeded, the body is not added.
 *
 * @param space Pointer to the physics space.
 * @param body Pointer to the body to add.
 *
 * @note The space does not manage the lifetime of the body.
 */
void fsSpaceAddBody(FsSpace* space, FsBody* body);

/**
 * @brief Advances the physics simulation.
 *
 * Steps the physics simulation forward using a fixed timestep.
 * Gravity, damping and velocity integration are applied.
 *
 * @param space Pointer to the physics space.
 * @param stepTime Simulation frequency (e.g. 60.0f for 60 Hz).
 *
 * @note Uses fsTimeGetDelta() internally.
 */
void fsSpaceStep(FsSpace* space, float stepTime);

/**
 * @brief Checks collision between two quad bodies.
 *
 * Performs an axis-aligned bounding box (AABB) collision test.
 * Only bodies of type FS_BODY_QUAD are supported.
 *
 * @param quad1 First body.
 * @param quad2 Second body.
 *
 * @return true if the bodies are colliding, false otherwise.
 */
bool fsIsQuadColiding(FsBody quad1, FsBody quad2);

/** @} */
