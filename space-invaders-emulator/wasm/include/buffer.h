#ifndef __BUFFER_H__

#include <GLES3/gl3.h> 
#include <stddef.h>

GLuint create_buffer(GLenum type, GLenum usage, size_t data_size, const void *data);

#endif