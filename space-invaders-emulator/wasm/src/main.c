#include <emscripten/html5.h>
#include <GLES3/gl3.h> 
#include <stdio.h>

#include "common.h"
#include "context.h"
#include "shader.h"
#include "vertex.h"

int running = 1;

GLuint default_prog;
GLuint vbo;
GLuint vao;

void main_loop() {
    if (!running) {
        emscripten_cancel_main_loop();
        return;
    }

    glClearColor(0.1f, 0.1f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(default_prog);
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);
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
        0.0f,  0.5f, 0.0f,   // top
       -0.5f, -0.5f, 0.0f,   // left
        0.5f, -0.5f, 0.0f    // right
    };
    vbo = create_vertex_buffer(GL_STATIC_DRAW, sizeof(vertices), vertices);

    vert_attr_t attributes[] = {
        { 
            .vbo = vbo,
            .size = 3,
            .type = GL_FLOAT,
            .normalized = GL_FALSE,
            .stride = 3 * sizeof(float),
            .pointer = (void*)0
        }
    };
    vao = create_vertex_array(ARRAY_LEN(attributes), attributes);

    emscripten_set_main_loop(main_loop, 0, 1);

    glDeleteProgram(default_prog);
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);

    return 0;
}