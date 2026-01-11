// Copyright (c) 2025-2026 Henrique Rodrigues Santos
// Licensed under the MIT License
// Github: https://github.com/saintsHr/Fireset

#pragma once

#include <GL/gl.h>
#include <stdint.h>
#include "fireset/vertex.h"
#include "fireset/image.h"

/**
 * @brief Direction enumeration.
 *
 * Represents the four cardinal directions commonly used
 * for movement, orientation, and logic in 2D space.
 */
typedef enum {
    FS_DIRECTION_UP,    /**< Upward direction */
    FS_DIRECTION_RIGHT, /**< Rightward direction */
    FS_DIRECTION_DOWN,  /**< Downward direction */
    FS_DIRECTION_LEFT   /**< Leftward direction */
} FsDirection;

/** 
 * @defgroup Render Render
 * @brief Basic 2D rendering primitives.
 * @{
 */

/**
 * @brief RGB color representation.
 *
 * Represents a color using three 8-bit integer components
 * in the RGB color space.
 */
typedef struct{
    uint8_t r; /**< Red component (0–255) */
    uint8_t g; /**< Green component (0–255) */
    uint8_t b; /**< Blue component (0–255) */
} FsColor;

/**
 * @brief Quadrilateral primitive.
 *
 * Represents a quadrilateral used for rendering and transformations.
 */
typedef struct{
    FsVec2 position;    /**< Position in window space */
    FsVec2 size;        /**< Size in window space */
    FsColor color;      /**< Color */
    float angle;        /**< Rotation angle in degrees */
} FsQuad;

/**
 * @brief Triangle primitive.
 *
 * Represents a triangle used for rendering and transformations.
 */
typedef struct{
    FsVec2 position;    /**< Position in window space */
    FsVec2 size;        /**< Size in window space */
    FsColor color;      /**< Color */
    float angle;        /**< Rotation angle in degrees */
} FsTriangle;

/**
 * @brief Point primitive.
 *
 * Represents a single point used for rendering.
 */
typedef struct{
    FsVec2 position;    /**< Position in window space */
    FsColor color;      /**< Color */
} FsPoint;

/**
 * @brief Circle primitive.
 *
 * Represents a circle used for rendering and transformations.
 */
typedef struct{
    FsVec2 position;    /**< Position in window space */
    FsVec2 size;        /**< Size in window space */
    FsColor color;      /**< Color */
    float angle;        /**< Rotation angle in degrees */
    int segments;       /**< Number of segments used to approximate the circle */
} FsCircle;

/**
 * @brief Line primitive.
 *
 * Represents a line used for rendering and transformations.
 */
typedef struct{
    FsVec2 position;    /**< Starting position in window space */
    float length;       /**< Line length */
    float angle;        /**< Rotation angle in degrees */
    float thickness;    /**< Line thickness */
    FsColor color;      /**< Color */
} FsLine;

/**
 * @brief Sprite structure.
 *
 * Represents a 2D textured sprite.
 */
typedef struct{
    FsVec2 position;    /**< Position in window space */
    FsVec2 size;        /**< Size in window space */
    FsTexture* texture; /**< Pointer to the sprite texture */
    float angle;        /**< Rotation angle in degrees */
    int texRot;         /**< Texture Rotation in 90°*/
} FsSprite;

/**
 * @brief Creates a triangle primitive.
 *
 * Initializes and returns a triangle with the given position, size,
 * color, and rotation angle.
 *
 * @param position Position of the triangle in window space.
 * @param size     Size of the triangle in window space.
 * @param color    Color of the triangle.
 * @param angle    Rotation angle in degrees.
 *
 * @return Initialized FsTriangle.
 */
FsTriangle FsTriangle_new(
    FsVec2 position,
    FsVec2 size,
    FsColor color,
    float angle
);

/**
 * @brief Creates a point primitive.
 *
 * Initializes and returns a point with the given position and color.
 *
 * @param position Position of the point in window space.
 * @param color    Color of the point.
 *
 * @return Initialized FsPoint.
 */
FsPoint FsPoint_new(
    FsVec2 position,
    FsColor color
);

/**
 * @brief Creates a line primitive.
 *
 * Initializes and returns a line with the given position, length,
 * thickness, color, and rotation angle.
 *
 * @param position  Starting position of the line in window space.
 * @param color     Color of the line.
 * @param angle     Rotation angle in degrees.
 * @param length    Length of the line.
 * @param thickness Thickness of the line.
 *
 * @return Initialized FsLine.
 */
FsLine FsLine_new(
    FsVec2 position,
    FsColor color,
    float angle,
    float length,
    float thickness
);

/**
 * @brief Creates a quadrilateral primitive.
 *
 * Initializes and returns a quad with the given position, size,
 * color, and rotation angle.
 *
 * @param position Position of the quad in window space.
 * @param size     Size of the quad in window space.
 * @param color    Color of the quad.
 * @param angle    Rotation angle in degrees.
 *
 * @return Initialized FsQuad.
 */
FsQuad FsQuad_new(
    FsVec2 position,
    FsVec2 size,
    FsColor color,
    float angle
);

/**
 * @brief Creates a circle primitive.
 *
 * Initializes and returns a circle with the given position, size,
 * color, rotation angle, and number of segments.
 *
 * @param position Position of the circle in window space.
 * @param size     Size of the circle in window space.
 * @param color    Color of the circle.
 * @param angle    Rotation angle in degrees.
 * @param segments Number of segments used to approximate the circle.
 *
 * @return Initialized FsCircle.
 */
FsCircle FsCircle_new(
    FsVec2 position,
    FsVec2 size,
    FsColor color,
    float angle,
    int segments
);

/**
 * @brief Creates a sprite.
 *
 * Initializes and returns a sprite with the given position, size,
 * texture, texture rotation, and rotation angle.
 *
 * @param position Position of the sprite in window space.
 * @param size     Size of the sprite in window space.
 * @param texture  Pointer to the texture used by the sprite.
 * @param texRot   Texture rotation mode or index.
 * @param angle    Rotation angle in degrees.
 *
 * @return Initialized FsSprite.
 *
 * @note The texture pointer must remain valid while the sprite is in use.
 */
FsSprite FsSprite_new(
    FsVec2 position,
    FsVec2 size,
    FsTexture* texture,
    int texRot,
    float angle
);

/**
 * @brief Calculates the angle to face a target position.
 *
 * Computes the rotation angle (in degrees) required for an object at
 * a given origin position to face a target position in 2D space.
 *
 * The resulting angle is adjusted based on the object's forward
 * direction, allowing different default orientations (up, right,
 * down, or left).
 *
 * @param origin   Origin position.
 * @param target   Target position to look at.
 * @param forward  Forward direction of the object.
 *
 * @return Angle in degrees required to face the target.
 */
float fsLookAt(FsVec2 origin, FsVec2 target, FsDirection forward);

/**
 * @brief Draws a pixel.
 *
 * Draws a colored point at the specified position.
 *
 * @param p Point to draw.
 * @param zindex Rendering order depth.
 */
void fsDrawPoint(const FsPoint* p, int zindex);

/**
 * @brief Draws a line.
 *
 * Draws a colored line.
 *
 * @param line Line to draw.
 * @param zindex Rendering order depth.
 */
void fsDrawLine(const FsLine* line, int zindex);

/**
 * @brief Draws a triangle.
 *
 * Draws a colored triangle.
 *
 * @param tri Triangle to draw.
 * @param zindex Rendering order depth.
 */
void fsDrawTriangle(const FsTriangle* tri, int zindex);

/**
 * @brief Draws a quadrilateral.
 *
 * Draws a colored quadrilateral.
 *
 * @param quad Quadrilateral to draw.
 * @param zindex Rendering order depth.
 */
void fsDrawQuad(const FsQuad* quad, int zindex);

/**
 * @brief Draws a circle.
 *
 * Draws a colored circle.
 *
 * @param circle Circle to draw.
 * @param zindex Rendering order depth.
 */
void fsDrawCircle(const FsCircle* circle, int zindex);

/**
 * @brief Draws a 2D sprite.
 *
 * Renders a textured sprite using its position, size,
 * rotation angle and texture.
 *
 * @param sprite Sprite to draw.
 * @param zindex Rendering order depth.
 *
 * @note The sprite texture must be valid and loaded.
 * @note Uses OpenGL immediate mode.
 */
void fsDrawSprite(const FsSprite* sprite, int zindex);

/**
 * @brief Sets the orthographic projection.
 *
 * Defines the orthographic rendering view.
 *
 * @param width  Width of the view.
 * @param height Height of the view.
 */
void fsOrthoSet(int width, int height);

/**
 * @brief Clears the window.
 *
 * Clears the window and OpenGL context using a color.
 *
 * @param color Clear color.
 */
void fsClear(FsColor color);

/**
 * @brief Creates an RGB color.
 *
 * @param r Red component (0–255).
 * @param g Green component (0–255).
 * @param b Blue component (0–255).
 *
 * @return Resulting color.
 */
FsColor FsColor_new(uint8_t r, uint8_t g, uint8_t b);

/** @} */