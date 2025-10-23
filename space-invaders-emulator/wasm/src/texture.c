#include "texture.h"

GLuint create_texture(tex_spec_t *spec) {
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    set_texture_params(spec->num_params, spec->params);   
    set_texture_data(spec);

    glBindTexture(GL_TEXTURE_2D, 0);
    return texture;
}

static void set_texture_params(size_t num_params, tex_param_t *params) {
    for (int i = 0; i < num_params; i++) {
        tex_param_t param = params[i];
        glTexParameteri(GL_TEXTURE_2D, param.name, param.value);
    }
}

static void set_texture_data(tex_spec_t *spec) {
    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        spec->internal_format,
        spec->width,
        spec->height,
        0,
        spec->format,
        spec->type,
        spec->data
    );
}