// Copyright (c) 2025 Henrique Rodrigues Santos
// Licensed under the MIT License
// Repo: https://github.com/saintsHr/Fireset

#include "fireset/audio.h"
#include "fireset/settings.h"
#include "fireset/fslog.h"

#include <sndfile.h>
#include <stdlib.h>
#include <stdbool.h>

FsSound fsSoundLoad(const char* filename){
    FsSound nullsnd = {0};

    FsSound sound = {0};
    SF_INFO info = {0};

    // opens file
    SNDFILE* file = sf_open(filename, SFM_READ, &info);
    if (!file){
        fsLog(FS_WARNING,"cannot open file '%s' (audio)", filename);
        return nullsnd;
    }

    // checks channels compability
    if (info.channels != 1 && info.channels != 2){
        fsLog(FS_WARNING,"file '%s' (audio) is not mono or stereo", filename);
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
    sound.samples = malloc(sound.frames * sound.channels * sizeof(short));
    if (!sound.samples){
        fsLog(FS_WARNING,"cannot allocate memory for '%s' (audio) samples", filename);
        return nullsnd;
    }

    // fills samples
    sf_count_t frames_read = sf_readf_short(file, sound.samples, sound.frames);
    if (frames_read != sound.frames){
        free(sound.samples);
        sf_close(file);
        fsLog(FS_WARNING,"failed to read some samples from '%s' (audio)", filename);
        return nullsnd;
    }

    // generates buffer
    ALuint buffer;
    alGenBuffers(1, &buffer);
    alBufferData(
        buffer,
        sound.format,
        sound.samples,
        sound.frames * sound.channels * sizeof(short),
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

void fsSoundSourcePlay(FsSound* sound, FsSoundSource* source, int volume){
    if (source->handle == 0) {
        alGenSources(1, &source->handle);
        alSourcei(source->handle, AL_BUFFER, sound->buffer);
        alSourcei(source->handle, AL_SOURCE_RELATIVE, AL_FALSE);
        alSource3f(source->handle, AL_POSITION, source->position.x, source->position.y, 0.0f);
        alSourcef(source->handle, AL_REFERENCE_DISTANCE, AUDIO_FULL_VOLUME_DISTANCE);
        alSourcef(source->handle, AL_ROLLOFF_FACTOR, AUDIO_DECAY_FACTOR);
    }

    // Volume
    float gain = volume / 100.0f;
    if (gain < 0.0f) gain = 0.0f;
    if (gain > 1.0f) gain = 1.0f;
    alSourcef(source->handle, AL_GAIN, gain);

    // Looping
    alSourcei(source->handle, AL_LOOPING, source->looping ? AL_TRUE : AL_FALSE);

    // Plays
    alSourcePlay(source->handle);
    source->playing = true;
}

void fsSoundSourceStop(FsSoundSource* source){
    if (!source) return;
    if (!source->handle) return;

    ALint state;
    alGetSourcei(source->handle, AL_SOURCE_STATE, &state);

    if (state == AL_PLAYING){
        alSourceStop(source->handle);
    }

    source->playing = false;
}

void fsSoundFree(FsSound* sound){
    if (!sound) return;
    free(sound->samples);
    sound->samples = NULL;
    sound->channels = 0;
    sound->sampleRate = 0;
    sound->frames = 0;
    sound->bps = 0;
}

void fsSoundSourceFree(FsSoundSource* source){
    if (!source || source->handle == 0) return;
    alSourceStop(source->handle);
    alDeleteSources(1, &source->handle);
    source->handle = 0;
}

void fsSoundListenerSetPosition(FsVec2 position){
    alListener3f(AL_POSITION, position.x, position.y, 0.0f);
}