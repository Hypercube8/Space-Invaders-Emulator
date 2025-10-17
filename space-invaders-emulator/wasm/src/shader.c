#include "shader.h"

GLuint create_shader_program(const char *vert_path, const char *frag_path) {
    GLuint shader_prog = glCreateProgram();

    GLuint vert_shader = create_shader(GL_VERTEX_SHADER, vert_path);
    GLuint frag_shader = create_shader(GL_FRAGMENT_SHADER, frag_path);
    glAttachShader(shader_prog, vert_shader);
    glAttachShader(shader_prog, frag_shader);
    link_shader_program(shader_prog);

    glDeleteShader(vert_shader);
    glDeleteShader(frag_shader);
    return shader_prog;
}

static GLuint create_shader(GLenum type, const char *path) {
    GLuint shader = glCreateShader(type);
    const GLchar *source = get_shader_source(path);
    glShaderSource(shader, 1, &source, NULL);
    compile_shader(shader);
    free(source);
    return shader;
}

static const GLchar *get_shader_source(const char *path) {
    FILE *file = fopen(path, "r");
    if (file == NULL) {
        SYS_ERROR(strcat("Failed to open file: ", path));
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *buffer = malloc(file_size + 1);
    if (buffer == NULL) {
        fclose(file);
        SYS_ERROR("Failed to allocate string buffer");
    }

    size_t bytes_read = fread(buffer, 1, file_size, file);
    if (bytes_read != file_size) {
        free(buffer);
        fclose(file);
        SYS_ERROR(strcat("Failed to read file: ", path));
    }

    buffer[file_size] = '\0';
    fclose(file);
    return (const GLchar*) buffer;
}

static void compile_shader(GLuint shader) {
    glCompileShader(shader);
    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        LOG_ERROR("Shader compilation failed: %s", infoLog);
    }
}

static void link_shader_program(GLuint shader_prog) {
    glLinkProgram(shader_prog);
    GLuint success;
    GLchar infoLog[512];
    glGetProgramiv(shader_prog, GL_LINK_STATUS, &success);
    
    if (!success) {
        glGetProgramInfoLog(shader_prog, 512, NULL, infoLog);
        LOG_ERROR("Unable to link shader program: %s", infoLog);
    }
}