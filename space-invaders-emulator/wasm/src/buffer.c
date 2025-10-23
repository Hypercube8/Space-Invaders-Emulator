#include "buffer.h"

GLuint create_buffer(GLenum type, GLenum usage, size_t data_size, const void *data) {
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(type, vbo);
    glBufferData(type, data_size, data, usage);
    glBindBuffer(type, 0);
    return vbo;
}