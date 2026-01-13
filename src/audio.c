// Copyright (c) 2025-2026 Henrique Rodrigues Santos
// Licensed under the MIT License
// Github: https://github.com/saintsHr/Fireset

#include "fireset/audio.h"
#include "fireset/settings.h"
#include "fireset/fslog.h"

#include <sndfile.h>
#include <stdlib.h>

FsSound fsSoundLoad(const char* filename){
    FsSound nullsnd = {0};

    FsSound sound = {0};
    SF_INFO info = {0};

    // opens file
    SNDFILE* file = sf_open(filename, SFM_READ, &info);
    if (!file){
        fsLog(FS_ERROR, FS_ASSETS,"Cannot open file '%s'.", filename);
        return nullsnd;
    }

    // checks channels compability
    if (info.channels != 1 && info.channels != 2){
        fsLog(FS_ERROR, FS_AUDIO,"File '%s' is not mono or stereo.", filename);
        return nullsnd;
    }

    // fills struct
    sound.channels   = info.channels;
    sound.frames     = info.frames;
    sound.sampleRate = info.samplerate;
    sound.bps        = 16;
    sound.format = (sound.channels == 1)
        ? AL_FORMAT_MONO16
        : AL_FORMAT_STEREO16;

    // allocates memory for samples
    sound.samples = malloc((size_t)sound.frames * (size_t)sound.channels * sizeof(short));
    if (!sound.samples){
        fsLog(FS_ERROR, FS_AUDIO, "Cannot allocate memory for '%s' samples.", filename);
        return nullsnd;
    }

    // fills samples
    sf_count_t frames_read = sf_readf_short(file, sound.samples, sound.frames);
    if (frames_read != sound.frames){
        free(sound.samples);
        sf_close(file);
        fsLog(FS_ERROR, FS_AUDIO, "Failed to read some samples from '%s'.", filename);
        return nullsnd;
    }

    size_t byteCount =
        (size_t)sound.frames *
        (size_t)sound.channels *
        sizeof(short);

    // generates buffer
    ALuint buffer;
    alGenBuffers(1, &buffer);
    alBufferData(
        buffer,
        sound.format,
        sound.samples,
        (ALsizei)byteCount,
        sound.sampleRate
    );
    sound.buffer = buffer;

    sf_close(file);
    return sound;
}

FsSoundSource fsSoundSourceCreate(FsVec2 position, bool looping){
    FsSoundSource source = {
        .handle = 0,
        .position = position,
        .playing = false,
        .looping = looping,
    };
    return source;
}

void fsSoundSourceHandle(int count, FsSoundSource* sources){
    for (int i = 0; i < count; i++){
        if (!sources[i].handle) continue;

        alSourcei(sources[i].handle, AL_LOOPING, sources[i].looping ? AL_TRUE : AL_FALSE);

        ALint state;
        alGetSourcei(sources[i].handle, AL_SOURCE_STATE, &state);

        if (sources[i].playing){
            if (state != AL_PLAYING){
                if (sources[i].looping){
                    alSourcePlay(sources[i].handle);
                } else {
                    sources[i].playing = false;
                }
            }
        } else {
            if (state == AL_PLAYING){
                alSourceStop(sources[i].handle);
            }
        }
    }
}

void fsSoundSourcePlay(FsSound* sound, FsSoundSource* source, float volume){
    if (source->handle == 0) {
        alGenSources(1, &source->handle);
        alSourcei(source->handle, AL_BUFFER, (ALint)sound->buffer);
        alSourcei(source->handle, AL_SOURCE_RELATIVE, AL_FALSE);
        alSource3f(source->handle, AL_POSITION, source->position.x, source->position.y, 0.0f);
        alSourcef(source->handle, AL_REFERENCE_DISTANCE, AUDIO_FULL_VOLUME_DISTANCE);
        alSourcef(source->handle, AL_ROLLOFF_FACTOR, AUDIO_DECAY_FACTOR);
    }

    // Volume
    if (volume < 0){
        fsLog(FS_WARNING, FS_AUDIO, "Volume out of range (received: %d). Clamped to 0.", volume);
        volume = 0;
    }
    if (volume > 100){
        fsLog(FS_WARNING, FS_AUDIO, "Volume out of range (received: %d). Clamped to 100.", volume);
        volume = 100;
    }

    float gain = volume / 100.0f;
    alSourcef(source->handle, AL_GAIN, gain);

    // Looping
    alSourcei(source->handle, AL_LOOPING, source->looping ? AL_TRUE : AL_FALSE);

    // Plays
    alSourcePlay(source->handle);
    source->playing = true;
}

void fsSoundSourceStop(FsSoundSource* source){
    if (!source){
        fsLog(FS_WARNING, FS_AUDIO, "Invalid or non-existing source provided.");
        return;
    }
    if (!source->handle){
        fsLog(FS_WARNING, FS_AUDIO, "Invalid or non-existing handle form source provided.");
        return;
    }

    ALint state;
    alGetSourcei(source->handle, AL_SOURCE_STATE, &state);

    if (state == AL_PLAYING){
        alSourceStop(source->handle);
    }

    source->playing = false;
}

void fsSoundFree(FsSound* sound){
    if (!sound){
        fsLog(FS_WARNING, FS_AUDIO, "Invalid or non-existing sound provided.");
        return;
    }

    free(sound->samples);
    sound->samples = NULL;
    sound->channels = 0;
    sound->sampleRate = 0;
    sound->frames = 0;
    sound->bps = 0;
}

void fsSoundSourceFree(FsSoundSource* source){
    if (!source){
        fsLog(FS_WARNING, FS_AUDIO, "Invalid or non-existing source provided.");
        return;
    }
    if (source->handle == 0){
        fsLog(FS_WARNING, FS_AUDIO, "Invalid or non-existing handle form source provided.");
        return;
    }
    alSourceStop(source->handle);
    alDeleteSources(1, &source->handle);
    source->handle = 0;
}

void fsSoundListenerSetPosition(FsVec2 position){
    alListener3f(AL_POSITION, position.x, position.y, 0.0f);
}