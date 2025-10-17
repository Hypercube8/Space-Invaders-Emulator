#ifndef __VERTEX_H__
#define __VERTEX_H__

#include <GLES3/gl3.h> 
#include <stddef.h>

typedef struct {
    GLuint vbo;
    GLint size;
    GLenum type;
    GLboolean normalized;
    GLsizei stride;
    const void *pointer;
} vert_attr_t;

GLuint create_vertex_buffer(GLenum usage, size_t data_size, const void *data);
GLuint create_vertex_array(size_t num_attr, vert_attr_t *attr_ptr);

static void set_attribute(GLuint vao, unsigned int index, vert_attr_t *attr);

#endif