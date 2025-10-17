#include "context.h"

void create_context(EmscriptenWebGLContextAttributes *attr) {
    EMSCRIPTEN_WEBGL_CONTEXT_HANDLE context_handle = emscripten_webgl_create_context(
        "#canvas", 
        attr
    );

    if (context_handle <= 0) {
        LOG_ERROR("Failed to create context");
    }

    emscripten_webgl_make_context_current(context_handle);
}