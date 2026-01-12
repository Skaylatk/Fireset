// Copyright (c) 2025-2026 Henrique Rodrigues Santos
// Licensed under the MIT License
// Github: https://github.com/saintsHr/Fireset

#include "fireset/image.h"
#include "fireset/fslog.h"

#include "fireset/stb_image.h"

FsImage fsImageLoad(const char* filename){
    FsImage image = {0};
    FsImage imagenull = {0};

    unsigned char* buffer = stbi_load(
        filename,
        &image.width,
        &image.height,
        NULL,
        4
    );

    if (buffer == NULL){
        fsLog(FS_ERROR, FS_ASSETS, "Cannot load image: '%s'", filename);
        return imagenull;
    }

    image.buffer = buffer;

    return image;
}

FsTexture fsTextureLoad(const char* filename){
    FsImage image = fsImageLoad(filename);
    FsTexture imagenull = {0};

    if (!image.buffer) return imagenull;

    GLuint tex;
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RGBA,
        image.width,
        image.height,
        0,
        GL_RGBA,
        GL_UNSIGNED_BYTE,
        image.buffer
    );

    stbi_image_free(image.buffer);
    image.buffer = NULL;

    glBindTexture(GL_TEXTURE_2D, tex);
    
    FsTexture texture = {
        tex,
        image.width,
        image.height
    };

    return texture;
}

void fsImageFree(FsImage* image){
    if (!image) return;

    if (image->buffer){
        stbi_image_free(image->buffer);
        image->buffer = NULL;
    }

    image->width = 0;
    image->height = 0;
}

void fsTextureFree(FsTexture* texture){
    if (!texture) return;

    if (texture->id){
        glDeleteTextures(1, &texture->id);
        texture->id = 0;
    }

    texture->width = 0;
    texture->height = 0;
}