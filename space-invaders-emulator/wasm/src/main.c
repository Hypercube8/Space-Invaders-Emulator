#include <emscripten/html5.h>
#include <GLES3/gl3.h> 
#include <stdio.h>

#include "common.h"
#include "context.h"
#include "shader.h"
#include "buffer.h"
#include "vertex.h"
#include "texture.h"

int running = 1;

GLuint default_prog;
GLuint vbo;
GLuint ebo;
GLuint vao;
GLuint tex;

void main_loop() {
    if (!running) {
        emscripten_cancel_main_loop();
        return;
    }

    glClearColor(0.1f, 0.1f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(default_prog);

    glBindTexture(GL_TEXTURE_2D, tex);
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

int main() {
    EmscriptenWebGLContextAttributes attr;
    emscripten_webgl_init_context_attributes(&attr);
    attr.alpha = 0;
    attr.depth = 1;
    attr.antialias = 1;
    attr.majorVersion = 2;
    attr.minorVersion = 0;
    create_context(&attr);

    default_prog = create_shader_program(
        "../shaders/default/vert.glsl", 
        "../shaders/default/frag.glsl"
    );

    float vertices[] = {
        //   Vertices     |  Texcoords   
        1.0f,  1.0f, 0.0f,  1.0f, 1.0f,   // top right
        1.0f, -1.0f, 0.0f,  1.0f, 0.0f,   // bottom right
       -1.0f, -1.0f, 0.0f,  0.0f, 0.0f,   // bottom left
       -1.0f,  1.0f, 0.0f,  0.0f, 1.0f    // top left
    };
    vbo = create_buffer(GL_ARRAY_BUFFER, GL_STATIC_DRAW, sizeof(vertices), vertices);

    GLuint indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };
    ebo = create_buffer(GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW, sizeof(indices), indices);

    vert_attr_t attributes[] = {
        { 
            .vbo = vbo,
            .size = 3,
            .type = GL_FLOAT,
            .normalized = GL_FALSE,
            .stride = 5 * sizeof(float),
            .pointer = (void*)0
        },
        {
            .vbo = vbo,
            .size = 2,
            .type = GL_FLOAT,
            .normalized = GL_FALSE,
            .stride = 5 * sizeof(float),
            .pointer = (void*)(3 * sizeof(float))
        }
    };
    vao = create_vertex_array(ebo, ARRAY_LEN(attributes), attributes);

    unsigned char *data = (unsigned char*)malloc(256 * 224 * 3);
    if (!data) {
        // Handle memory allocation failure
        perror("Failed to allocate memory for texture data");
        return 1;
    }

    // Fill the data buffer with all white pixels
    for (int i = 0; i < 256 * 224 * 3; ++i) {
        data[i] = 255;
    }

    tex_param_t params[] = { 
        {
            .name = GL_TEXTURE_WRAP_S,
            .value = GL_REPEAT,
        },
        {
            .name = GL_TEXTURE_WRAP_T,
            .value = GL_REPEAT
        },
        {
            .name = GL_TEXTURE_MIN_FILTER,
            .value = GL_NEAREST,
        },
        {
            .name = GL_TEXTURE_MAG_FILTER,
            .value = GL_NEAREST
        }
    };

    tex_spec_t spec = {
        .internal_format = GL_RGB,
        .format = GL_RGB,
        .type = GL_UNSIGNED_BYTE,
        .num_params = ARRAY_LEN(params),
        .params = params
    };
    spec.width = 256;
    spec.height = 224;
    spec.data = data;
    tex = create_texture(&spec);

    emscripten_set_main_loop(main_loop, 0, 1);

    glDeleteProgram(default_prog);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);
    glDeleteVertexArrays(1, &vao);
    free(data);
    glDeleteTextures(1, &tex);

    return 0;
}