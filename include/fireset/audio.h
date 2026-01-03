#pragma once

#include <AL/al.h>
#include <AL/alc.h>

#include "fireset/vertex.h"

/** 
 * @defgroup Audio Audio
 * @brief 2D positional sound using OpenAL.
 * @{
 */

/**
 * @brief Represents a loaded sound buffer.
 *
 * Contains audio data and OpenAL buffer information.
 */
typedef struct {
    int channels;    /**< Number of channels (1 = mono, 2 = stereo) */
    int sampleRate;  /**< Sample rate in Hz */
    int bps;         /**< Bits per sample (usually 16) */
    int frames;      /**< Total number of frames */
    short* samples;  /**< Raw PCM samples */
    ALenum format;   /**< OpenAL format (AL_FORMAT_MONO16 or AL_FORMAT_STEREO16) */
    ALuint buffer;   /**< OpenAL buffer handle */
} FsSound;

/**
 * @brief Represents a sound source in 2D space.
 *
 * Contains information for playback, looping, and position.
 */
typedef struct {
    ALuint handle;   /**< OpenAL source handle */
    FsVec2 position; /**< 2D position of the sound source */
    bool looping;    /**< Should the sound loop? */
    bool playing;    /**< Is the sound currently playing? */
} FsSoundSource;

/**
 * @brief Loads a sound from file.
 *
 * Loads a sound file using libsndfile and generates an OpenAL buffer.
 *
 * @param filename Path to the audio file.
 * @return FsSound structure containing audio data and buffer.
 */
FsSound fsSoundLoad(const char* filename);

/**
 * @brief Frees a loaded sound.
 *
 * Frees the sample memory and resets the FsSound structure.
 *
 * @param sound Pointer to the FsSound to free.
 */
void fsSoundFree(FsSound* sound);

/**
 * @brief Creates a new sound source.
 *
 * Initializes a FsSoundSource at a given position.
 *
 * @param position 2D position of the source.
 * @param looping Should the source loop when played.
 * @return FsSoundSource initialized but not playing.
 */
FsSoundSource fsSoundSourceCreate(FsVec2 position, bool looping);

/**
 * @brief Plays a sound on a source.
 *
 * Binds the sound to the source, sets volume, looping, and plays it.
 *
 * @param sound Pointer to the loaded FsSound.
 * @param source Pointer to the FsSoundSource.
 * @param volume Volume in percentage (0–100).
 */
void fsSoundSourcePlay(FsSound* sound, FsSoundSource* source, int volume);

/**
 * @brief Stops a sound source.
 *
 * Stops playback if the source is currently playing.
 *
 * @param source Pointer to the FsSoundSource to stop.
 */
void fsSoundSourceStop(FsSoundSource* source);

/**
 * @brief Frees a sound source.
 *
 * Stops playback and deletes the OpenAL source.
 *
 * @param source Pointer to the FsSoundSource to free.
 */
void fsSoundSourceFree(FsSoundSource* source);

/**
 * @brief Updates multiple sound sources.
 *
 * Handles playback state, looping, and stopping for an array of sources.
 *
 * @param count Number of sources in the array.
 * @param sources Array of FsSoundSource to handle.
 */
void fsSoundSourceHandle(int count, FsSoundSource* sources);

/** @} */