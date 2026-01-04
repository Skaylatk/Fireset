// Copyright (c) 2025 Henrique Rodrigues Santos
// Licensed under the MIT License
// Repo: https://github.com/saintsHr/Fireset

#pragma once

/** 
 * @defgroup Time Time
 * @brief Time-related functions.
 * @{
 */

/**
 * @brief Returns the current system time.
 *
 * Returns the current system time at the moment this function is called.
 *
 * @return Current system time.
 */
double fsTimeGetSystemTime(void);

/**
 * @brief Returns the delta time.
 *
 * Returns the time difference between the current frame and the previous one.
 *
 * @return Delta time.
 */
double fsTimeGetDelta(void);

/**
 * @brief Returns the engine running time.
 *
 * Returns the elapsed time, in seconds, since the time system
 * was initialized with fsTimeInit().
 *
 * This function provides a monotonic, engine-relative time value
 * and should be used for timing, animations, logging, and
 * time-based calculations inside the engine.
 *
 * @return Time in seconds since fsTimeInit() was called.
 *
 * @note This value is independent of the system clock and
 *       is not affected by system time changes.
 * @note The returned value always increases while the engine runs.
 */
double fsTimeGetTime(void);

/**
 * @brief Initializes the time module.
 *
 * Initializes the internal time tracking used by the engine.
 *
 * This function must be called before using any other time-related function.
 */
void fsTimeInit(void);

/** 
 * @brief Waits for a specified duration.
 *
 * Pauses the program execution for a given number of milliseconds.
 * Works on Windows and POSIX systems.
 *
 * @param ms Duration to wait, in milliseconds.
 *
 * @note On Windows, uses `Sleep()`.
 * @note On Linux/macOS, uses `nanosleep()` and handles `EINTR`.
 */
void fsWait(unsigned long ms);

/** @} */