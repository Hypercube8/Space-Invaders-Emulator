#include "vertex.h"

GLuint create_vertex_buffer(GLenum usage, size_t data_size, const void *data) {
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, data_size, data, usage);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    return vbo;
}

GLuint create_vertex_array(size_t num_attr, vert_attr_t *attr_ptr) {
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    for (unsigned int i = 0; i < num_attr; i++) {
        vert_attr_t attr = attr_ptr[i];
        set_attribute(vao, i, &attr);
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    return vao;
}

static void set_attribute(GLuint vao, unsigned int index, vert_attr_t *attr) {
    glBindBuffer(GL_ARRAY_BUFFER, attr->vbo);
    glVertexAttribPointer(index, 
        attr->size, 
        attr->type, 
        attr->normalized, 
        attr->stride,
        attr->pointer
    );
    glEnableVertexAttribArray(index);
}