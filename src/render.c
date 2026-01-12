// Copyright (c) 2025-2026 Henrique Rodrigues Santos
// Licensed under the MIT License
// Github: https://github.com/saintsHr/Fireset

#include "fireset/render.h"
#include "fireset/settings.h"
#include "fireset/fslog.h"
#include <math.h>

float fsLookAt(FsVec2 origin, FsVec2 target, FsDirection forward){
    float dx = target.x - origin.x;
    float dy = target.y - origin.y;

    float base_angle = atan2f(dy, dx) * (180.0f / PI);
    float angle = base_angle;

    switch(forward){
        case FS_DIRECTION_UP:
            angle = base_angle - 90.0f;
            break;

        case FS_DIRECTION_RIGHT:
            angle = base_angle;
            break;

        case FS_DIRECTION_DOWN:
            angle = base_angle + 90.0f;
            break;

        case FS_DIRECTION_LEFT:
            angle = base_angle - 180.0f;
            break;

        default:
            angle = 0;
            break;
    }

    return angle;
}

void fsDrawTriangle(const FsTriangle* tri, int zindex){
    if (zindex < 1) zindex = 1;
    if (zindex > REND_MAX_ZINDEX) zindex = REND_MAX_ZINDEX;

    float z = -1.0f + ((float)zindex / REND_MAX_ZINDEX);

    glPushMatrix();
        glTranslatef(tri->position.x, tri->position.y, z);
        glRotatef(tri->angle, 0, 0, 1.0f);
        glScalef(tri->size.x, tri->size.y, 1.0f);

        glColor3f(
            tri->color.r / 255.0f,
            tri->color.g / 255.0f,
            tri->color.b / 255.0f
        );
        glBegin(GL_TRIANGLES);
            glVertex2f( 0.0f,   -0.5f);
            glVertex2f(-0.433f,  0.25f);
            glVertex2f( 0.433f,  0.25f);
        glEnd();
    glPopMatrix();
}

void fsDrawPoint(const FsPoint* p, int zindex){
    if (zindex < 1) zindex = 1;
    if (zindex > REND_MAX_ZINDEX) zindex = REND_MAX_ZINDEX;

    float z = -1.0f + ((float)zindex / REND_MAX_ZINDEX); 

    glPushMatrix();
        glTranslatef(p->position.x, p->position.y, z);

        glColor3f(
            p->color.r / 255.0f,
            p->color.g / 255.0f,
            p->color.b / 255.0f
        );

        glBegin(GL_POINTS);
            glVertex2f(0.0f, 0.0f);
        glEnd();
    glPopMatrix();
}

void fsDrawLine(const FsLine* line, int zindex){
    if (zindex < 1) zindex = 1;
    if (zindex > REND_MAX_ZINDEX) zindex = REND_MAX_ZINDEX;

    float z = -1.0f + ((float)zindex / REND_MAX_ZINDEX);

    glPushMatrix();
        glTranslatef(line->position.x, line->position.y, z);
        glRotatef(line->angle, 0.0f, 0.0f, 1.0f);
        glScalef(line->length, line->thickness, 1.0f);

        glColor3f(
            line->color.r / 255.0f,
            line->color.g / 255.0f,
            line->color.b / 255.0f
        );

        glBegin(GL_QUADS);
            glVertex2f(0.0f, -0.5f);
            glVertex2f(1.0f, -0.5f);
            glVertex2f(1.0f,  0.5f);
            glVertex2f(0.0f,  0.5f);
        glEnd();
    glPopMatrix();
}

void fsDrawQuad(const FsQuad* quad, int zindex){
    if (zindex < 0) zindex = 0;
    if (zindex > REND_MAX_ZINDEX) zindex = REND_MAX_ZINDEX;

    float z = -1.0f + 2.0f * ((float)zindex / REND_MAX_ZINDEX);

    glPushMatrix();
        glTranslatef(quad->position.x, quad->position.y, z);
        glRotatef(quad->angle, 0, 0, 1.0f);
        glScalef(quad->size.x, quad->size.y, 1.0f);

        glColor3f(
            quad->color.r / 255.0f,
            quad->color.g / 255.0f,
            quad->color.b / 255.0f
        );

        glBegin(GL_QUADS);
            glVertex2f(-0.5f, -0.5f);
            glVertex2f( 0.5f, -0.5f);
            glVertex2f( 0.5f,  0.5f);
            glVertex2f(-0.5f,  0.5f);
        glEnd();
    glPopMatrix();
}

void fsDrawCircle(const FsCircle* circle, int zindex){
    if (zindex < 1) zindex = 1;
    if (zindex > REND_MAX_ZINDEX) zindex = REND_MAX_ZINDEX;

    float z = -1.0f + ((float)zindex / REND_MAX_ZINDEX);

    int segments = circle->segments;
    if (segments < REND_MIN_SEGMENTS) segments = REND_MIN_SEGMENTS;
    if (segments > REND_MAX_SEGMENTS) segments = REND_MAX_SEGMENTS;

    glPushMatrix();
        glTranslatef(circle->position.x, circle->position.y, z);
        glRotatef(circle->angle, 0.0f, 0.0f, 1.0f);
        glScalef(circle->size.x, circle->size.y, 1.0f);

        glColor3f(
            circle->color.r / 255.0f,
            circle->color.g / 255.0f,
            circle->color.b / 255.0f
        );

        glBegin(GL_TRIANGLE_FAN);
            glVertex2f(0.0f, 0.0f);
            for(int i = 0; i <= segments; i++){
                float theta = (float)i / (float)segments * 2.0f * PI;
                float x = cosf(theta) * 0.5f;
                float y = sinf(theta) * 0.5f;
                glVertex2f(x, y);
            }
        glEnd();
    glPopMatrix();
}

void fsDrawSprite(const FsSprite* sprite, int zindex){
    if (zindex < 1) zindex = 1;
    if (zindex > REND_MAX_ZINDEX) zindex = REND_MAX_ZINDEX;

    float z = -1.0f + ((float)zindex / REND_MAX_ZINDEX);

    glDepthMask(GL_FALSE);
        glPushMatrix();
            glTranslatef(sprite->position.x, sprite->position.y, z);
            glRotatef(sprite->angle, 0, 0, 1.0f);
            glScalef(sprite->size.x, sprite->size.y, 1.0f);

            glEnable(GL_TEXTURE_2D);
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

            glBindTexture(GL_TEXTURE_2D, sprite->texture->id);

            glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

            float u[4] = {0.0f, 1.0f, 1.0f, 0.0f};
            float v[4] = {0.0f, 0.0f, 1.0f, 1.0f};

            int rotIdx[4];
            switch(sprite->texRot % 4){
                case 0: rotIdx[0]=0; rotIdx[1]=1; rotIdx[2]=2; rotIdx[3]=3; break; // 0°
                case 1: rotIdx[0]=3; rotIdx[1]=0; rotIdx[2]=1; rotIdx[3]=2; break; // 90°
                case 2: rotIdx[0]=2; rotIdx[1]=3; rotIdx[2]=0; rotIdx[3]=1; break; // 180°
                case 3: rotIdx[0]=1; rotIdx[1]=2; rotIdx[2]=3; rotIdx[3]=0; break; // 270°
            }

            glBegin(GL_QUADS);
                for(int i=0; i<4; i++){
                    glTexCoord2f(u[rotIdx[i]], v[rotIdx[i]]);
                    switch(i){
                        case 0: glVertex2f(-0.5f, -0.5f); break;
                        case 1: glVertex2f(0.5f, -0.5f); break;
                        case 2: glVertex2f(0.5f, 0.5f); break;
                        case 3: glVertex2f(-0.5f, 0.5f); break;
                    }
                }
            glEnd();

            glDisable(GL_BLEND);
            glDisable(GL_TEXTURE_2D);
        glPopMatrix();
    glDepthMask(GL_TRUE);
}

void fsClear(FsColor color){
    glClearColor(
        color.r / 255.0f,
        color.g / 255.0f,
        color.b / 255.0f,
        1.0f
    );

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void fsOrthoSet(int width, int height){
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, height, 0, -1.0f, 1.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}