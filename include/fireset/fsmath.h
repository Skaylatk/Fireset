// Copyright (c) 2025-2026 Henrique Rodrigues Santos
// Licensed under the MIT License
// Github: https://github.com/saintsHr/Fireset

#pragma once

#include "fireset/vector.h"
#include "fireset/color.h"

/**
 * @brief Adds two 2D vectors.
 *
 * @param vec1 First vector.
 * @param vec2 Second vector.
 *
 * @return Resulting vector (vec1 + vec2).
 */
FsVec2 fsVecAdd(FsVec2 vec1, FsVec2 vec2);

/**
 * @brief Subtracts one 2D vector from another.
 *
 * @param vec1 First vector.
 * @param vec2 Second vector.
 *
 * @return Resulting vector (vec1 - vec2).
 */
FsVec2 fsVecSub(FsVec2 vec1, FsVec2 vec2);

/**
 * @brief Multiplies two 2D vectors component-wise.
 *
 * @param vec1 First vector.
 * @param vec2 Second vector.
 *
 * @return Resulting vector (vec1 * vec2).
 */
FsVec2 fsVecMul(FsVec2 vec1, FsVec2 vec2);

/**
 * @brief Divides two 2D vectors component-wise.
 *
 * @param vec1 First vector.
 * @param vec2 Second vector.
 *
 * @param vec2 Second vector.
 *
 * @return Resulting vector (vec1 / vec2).
 */
FsVec2 fsVecDiv(FsVec2 vec1, FsVec2 vec2);

/**
 * @brief Inverts an RGB color.
 *
 * Each color channel is inverted using:
 * inverted = 255 - value
 *
 * @param color Original color.
 *
 * @return Inverted color.
 */
FsColor fsColorInvert(FsColor color);