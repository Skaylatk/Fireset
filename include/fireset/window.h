// Copyright (c) 2025 Henrique Rodrigues Santos
// Licensed under the MIT License
// Repo: https://github.com/saintsHr/Fireset

#pragma once

#include <GLFW/glfw3.h>
#include <stdbool.h>

#include "fireset/vertex.h"

/** 
 * @defgroup Window Window
 * @brief Window management functions and types.
 * @{
 */

/**
 * @brief Window object.
 *
 * Represents a window and its associated backend handle.
 */
typedef struct{
    GLFWwindow* handle; /**< Backend window handle. */
    int width;          /**< Width of the window in pixels. */
    int height;         /**< Height of the window in pixels. */
    const char* name;         /**< Window title. */
} FsWindow;

/**
 * @brief Creates a window.
 *
 * Initializes a window using the provided data.
 *
 * @param name The name/title of the generated window.
 * @param size The Vec2 size of the window.
 * @return Pointer to the created window.
 */
FsWindow fsWindowCreate(const char* name, FsVec2 size);

/**
 * @brief Updates a window.
 *
 * Processes events and updates the internal state of the window.
 *
 * @param window Window to update.
 */
void fsWindowHandle(FsWindow* window);

/**
 * @brief Destroys a window.
 *
 * Closes the window and releases its resources.
 *
 * @param window Window to destroy.
 */
void fsWindowDestroy(FsWindow* window);

/**
 * @brief Checks if a window should close.
 *
 * Queries the window to determine if a close request has been issued.
 *
 * @param window Window to check.
 * @return true if the window should close, false otherwise.
 */
bool fsWindowShouldClose(FsWindow* window);

/** @} */