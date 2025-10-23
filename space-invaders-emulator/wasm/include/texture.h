#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include <GLES3/gl3.h> 
#include <stddef.h>

#include "common.h"

typedef struct {
    GLenum name;
    GLenum value;
} tex_param_t;

typedef struct {
    GLint internal_format;
    GLsizei width;
    GLsizei height;
    GLenum format;
    GLenum type;
    size_t num_params;
    tex_param_t *params;
    void *data;
} tex_spec_t;

GLuint create_texture(tex_spec_t *spec);

static void set_texture_params(size_t num_params, tex_param_t *params);
static void set_texture_data(tex_spec_t *spec);

#endif 