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

GLuint create_vertex_array(GLuint ebo, size_t num_attr, vert_attr_t *attr_ptr);

static void set_attributes(GLuint vao, size_t num_attr, vert_attr_t *attr_ptr);

#endif