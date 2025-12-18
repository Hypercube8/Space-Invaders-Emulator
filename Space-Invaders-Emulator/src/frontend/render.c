#include "frontend/render.h"

static char *read_shader_source(const char *path) {
    FILE *fptr = fopen(path, "rb");

    if (fptr == NULL) {
        perror("Failed to open file.");
    }

    fseek(fptr, 0, SEEK_END);
    size_t length = ftell(fptr);
    rewind(fptr);

    const char *buffer = malloc(length * sizeof(char));
    fread(buffer, sizeof(char), length, fptr);
    fclose(fptr);

    return buffer;
}

static GLuint create_shader(const char *path, GLenum type) {
    const char *source = read_shader_source(path);
    
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);

    int success;
    GLchar infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    free(source);


}