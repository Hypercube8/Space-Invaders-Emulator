#include <SDL.h>
#include <SDL_opengl.h>
#include <emscripten.h>

SDL_Window *window;
SDL_GLContext glContext;
int running = 1;

void main_loop() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) running = 0;
    }

    // Set clear color and clear the screen
    glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    SDL_GL_SwapWindow(window);

    if (!running) {
        emscripten_cancel_main_loop();
    }
}

int main(int argc, char *argv[]) {
    SDL_Init(SDL_INIT_VIDEO);

    // Create window with OpenGL context
    window = SDL_CreateWindow("SDL OpenGL Emscripten",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              640, 480,
                              SDL_WINDOW_OPENGL);

    glContext = SDL_GL_CreateContext(window);

    // Use emscripten_set_main_loop for rendering loop
    emscripten_set_main_loop(main_loop, 0, 1);

    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}