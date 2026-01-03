#include "fireset/audio.h"
#include "fireset/settings.h"

#include <sndfile.h>
#include <stdlib.h>
#include <stdbool.h>

static FsSoundSource g_sources[AUDIO_MAX_SOURCES];
static int g_sourceCount = 0;

FsSound fsSoundLoad(const char* filename){
    FsSound sound = {0};
    SF_INFO info = {0};

    // opens file
    SNDFILE* file = sf_open(filename, SFM_READ, &info);
    if (!file) return sound;

    // checks channels compability
    if (info.channels != 1 && info.channels != 2) return sound;

    // fills struct
    sound.channels   = info.channels;
    sound.frames     = info.frames;
    sound.sampleRate = info.samplerate;
    sound.bps        = 16;
    sound.format = (sound.channels == 1)
        ? AL_FORMAT_MONO16
        : AL_FORMAT_STEREO16;

    // fills samples
    sound.samples = malloc(sound.frames * sound.channels * sizeof(short));
    sf_readf_short(file, sound.samples, sound.frames);
    if (!sound.samples){
        sf_close(file);
        return sound;
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

void fsSoundPlay(const FsSound* sound, const FsSoundSource* source, int volume){
    ALuint src;
    alGenSources(1, &src);

    alSourcei(src, AL_BUFFER, sound->buffer);
    alSourcei(src, AL_SOURCE_RELATIVE, AL_FALSE);

    // position
    alSource3f(src, AL_POSITION, source->position.x, source->position.y, 0.0f);

    // attenuation
    alSourcef(src, AL_REFERENCE_DISTANCE, AUDIO_FULL_VOLUME_DISTANCE);
    alSourcef(src, AL_ROLLOFF_FACTOR, AUDIO_DECAY_FACTOR);

    // volume
    float gain = volume / 100.0f;
    if (gain < 0.0f) gain = 0.0f;
    if (gain > 1.0f) gain = 1.0f;
    alSourcef(src, AL_GAIN, gain);

    // plays the audio
    alSourcePlay(src);
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