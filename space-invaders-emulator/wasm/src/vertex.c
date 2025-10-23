#include "vertex.h"

GLuint create_vertex_array(GLuint ebo, size_t num_attr, vert_attr_t *attr_ptr) {
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

    set_attributes(vao, num_attr, attr_ptr);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    return vao;
}

static void set_attributes(GLuint vao, size_t num_attr, vert_attr_t *attr_ptr) {
    for (int i = 0; i < num_attr; i++) {
        vert_attr_t attr = attr_ptr[i];

        glBindBuffer(GL_ARRAY_BUFFER, attr.vbo);
        glVertexAttribPointer(i, 
            attr.size, 
            attr.type, 
            attr.normalized, 
            attr.stride,
            attr.pointer
        );
        glEnableVertexAttribArray(i);
    }
}