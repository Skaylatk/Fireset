// Copyright (c) 2025-2026 Henrique Rodrigues Santos
// Licensed under the MIT License
// Github: https://github.com/saintsHr/Fireset

#pragma once

#include <stdint.h>
#include "GL/gl.h"

/**
 * @brief Image data structure.
 *
 * Represents a loaded image in system memory.
 */
typedef struct{
    uint8_t* buffer; /**< Pointer to the image pixel data (RGBA, 8-bit per channel). */
    int width;       /**< Width of the image in pixels. */
    int height;      /**< Height of the image in pixels. */
}FsImage;

/**
 * @brief Texture data structure.
 *
 * Represents an OpenGL 2D texture.
 */
typedef struct{
    GLuint id;   /**< OpenGL texture ID. */
    int width;   /**< Width of the texture in pixels. */
    int height;  /**< Height of the texture in pixels. */
}FsTexture;

/**
 * @brief Loads an image from a file.
 *
 * Loads an image from the specified file using stb_image and returns
 * an FsImage struct containing the image data.
 *
 * @param filename Path to the image file.
 * @return FsImage struct containing:
 *         - buffer: pointer to the image pixel data (RGBA, 8-bit per channel)
 *         - width: width of the image in pixels
 *         - height: height of the image in pixels
 *
 * @note The caller is responsible for freeing `buffer` using `stbi_image_free`
 *       when the image is no longer needed.
 */
FsImage fsImageLoad(const char* filename);

/**
 * @brief Loads a texture from an image file.
 *
 * Loads an image from the specified file and creates an OpenGL 2D texture.
 * Returns an FsTexture struct containing the texture ID and its dimensions.
 *
 * @param filename Path to the image file.
 * @return FsTexture struct containing:
 *         - id: OpenGL texture ID
 *         - width: texture width in pixels
 *         - height: texture height in pixels
 *
 * @note The texture uses GL_LINEAR filtering for minification and magnification,
 *       and GL_REPEAT wrapping.
 * @note The caller is responsible for freeing the texture using `glDeleteTextures`
 *       when it is no longer needed.
 */
FsTexture fsTextureLoad(const char* filename);

/**
 * @brief Frees an image.
 *
 * Releases the memory associated with an image buffer
 * previously loaded by the engine.
 *
 * After calling this function, the image is reset to
 * a safe empty state.
 *
 * @param image Pointer to the FsImage to free.
 */
void fsImageFree(FsImage* image);

/**
 * @brief Frees a texture.
 *
 * Deletes the OpenGL texture associated with the given
 * texture object and resets its data.
 *
 * @param texture Pointer to the FsTexture to free.
 *
 * @note Requires a valid OpenGL context.
 */
void fsTextureFree(FsTexture* texture);
