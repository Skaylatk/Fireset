// Copyright (c) 2025 Henrique Rodrigues Santos
// Licensed under the MIT License
// Repo: https://github.com/saintsHr/Fireset

#define STB_IMAGE_IMPLEMENTATION
#include "fireset/stb_image.h"

#include "fireset/core.h"
#include "fireset/fstime.h"

#include <AL/al.h>
#include <AL/alc.h>

static ALCdevice* g_device = NULL;
static ALCcontext* g_context = NULL;

bool fsInit(void){
    if(!glfwInit()) return false;
    fsTimeInit();
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    g_device = alcOpenDevice(NULL);
    if (!g_device) return false;

    g_context = alcCreateContext(g_device, NULL);
    if (!g_context){
        alcCloseDevice(g_device);
        return false;
    }

    alcMakeContextCurrent(g_context);

    return true;
}

void fsExit(void){
    if(g_context) {
        alcMakeContextCurrent(NULL);
        alcDestroyContext(g_context);
        g_context = NULL;
    }

    if(g_device) {
        alcCloseDevice(g_device);
        g_device = NULL;
    }

    alcMakeContextCurrent(NULL);
    
    glfwTerminate();
}