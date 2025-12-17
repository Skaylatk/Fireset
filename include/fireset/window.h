#pragma once

#include <GLFW/glfw3.h>
#include <stdbool.h>

/** 
 * @defgroup Window
 * @{
 */

/**
 * @brief Window struct.
 * 
 * Window struct & type, used to manage an window object.
 */
typedef struct{
    GLFWwindow* handle; /**< Backend of the window. */
    int width; /**< Total width of the window in pixels. */
    int height; /**< Total height of the window in pixels. */
    char* name;  /**< Title/name of the window. */
}FsWindow;

/**
 * @brief Creates a window.
 * 
 * Uses window data to create and setup an window.
 * 
 * @param window Window struct, used as data to create a window.
 */
FsWindow* fsCreateWindow(FsWindow* window);

/**
 * @brief Window handler.
 * 
 * Function used to keep a window open and updated.
 * 
 * @param window Window to handle.
 */
void fsHandleWindow(FsWindow* window);

/**
 * @brief Destroys a Window.
 * 
 * Function used to destroy and close an window.
 * 
 * @param window Window to destroy.
 */
void fsDestroyWindow(FsWindow* window);

/**
 * @brief Checks if window should close.
 * 
 * Function used check if a provided window should close.
 * 
 * @param window Window to check.
 */
bool fsWindowShouldClose(FsWindow window);

/** @} */