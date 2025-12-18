#ifndef __RENDER_H__
#define __RENDER_H__

#include <GLES3/gl3.h>

#include "backend/core.h"

typedef struct {
    GLuint vao;
} renderer_t;

void setup_triangle();
void draw_triangle();

#endif