#ifndef __SHADER_H__
#define __SHADER_H__

#include <GLES3/gl3.h> 
#include <stdio.h>
#include <stdlib.h>

#include "common.h"

GLuint create_shader_program(const char *vert_path, const char *frag_path);

static GLuint create_shader(GLenum type, const char *path);
static void link_shader_program(GLuint shader_prog);
static const GLchar *get_shader_source(const char *path);
static void compile_shader(GLuint shader);

#endif