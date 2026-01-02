// Copyright (c) 2025 Henrique Rodrigues Santos
// Licensed under the MIT License
// Repo: https://github.com/saintsHr/Fireset

#pragma once

#include <GL/gl.h>
#include <stdint.h>
#include "fireset/vertex.h"
#include "fireset/image.h"

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
    FsVec2 position; /**< Position in window space */
    FsVec2 size;     /**< Size in window space */
    FsColor color;   /**< Color */
    float angle;     /**< Rotation angle in degrees */
} FsQuad;

/**
 * @brief Triangle primitive.
 *
 * Represents a triangle used for rendering and transformations.
 */
typedef struct{
    FsVec2 position; /**< Position in window space */
    FsVec2 size;     /**< Size in window space */
    FsColor color;   /**< Color */
    float angle;     /**< Rotation angle in degrees */
} FsTriangle;

/**
 * @brief Point primitive.
 *
 * Represents a single point used for rendering.
 */
typedef struct{
    FsVec2 position; /**< Position in window space */
    FsColor color;   /**< Color */
} FsPoint;

/**
 * @brief Circle primitive.
 *
 * Represents a circle used for rendering and transformations.
 */
typedef struct{
    FsVec2 position; /**< Position in window space */
    FsVec2 size;     /**< Size in window space */
    FsColor color;   /**< Color */
    float angle;     /**< Rotation angle in degrees */
    int segments;    /**< Number of segments used to approximate the circle */
} FsCircle;

/**
 * @brief Line primitive.
 *
 * Represents a line used for rendering and transformations.
 */
typedef struct{
    FsVec2 position; /**< Starting position in window space */
    float length;    /**< Line length */
    float angle;     /**< Rotation angle in degrees */
    float thickness; /**< Line thickness */
    FsColor color;   /**< Color */
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
} FsSprite;

/**
 * @brief Draws a pixel.
 *
 * Draws a colored point at the specified position.
 *
 * @param p Point to draw.
 * @param zindex Rendering order depth.
 */
void fsDrawPixel(const FsPoint* p, int zindex);

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