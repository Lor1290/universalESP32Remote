#define SDL_MAIN_USE_CALLBACKS 1
#define SDL_FLAGS (SDL_INIT_VIDEO)

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>


static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;
static SDL_FPoint points[500];


SDL_AppResult SDL_AppInit(void** appstate, int argc, char* argv[]) {
    SDL_SetAppMetadata("myFirstApp", "1.0", "com.example.firstApp");

    if(!SDL_Init(SDL_FLAGS)) {
        SDL_Log("[!] An error occured while trying to initialize SDL3 %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    window = SDL_CreateWindow("myFirstApp", 600, 400, SDL_WINDOW_RESIZABLE);
    if(!window) {
        SDL_Log("[!] An error occured while trying to initialize a Window %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    renderer = SDL_CreateRenderer(window, NULL);
    if(!renderer) {
        SDL_Log("[!] An error occured while trying to initialize a Renderer %s", SDL_GetError());
    }

    SDL_SetRenderLogicalPresentation(renderer, 600,  400, SDL_LOGICAL_PRESENTATION_LETTERBOX);

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event) {
    if(event->type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS;
    }
    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void* appstate) {
    const double now = ((double) SDL_GetTicks()) / 1000.0;

    const float red = (float)(0.5 + 0.5 + SDL_sin(now));
    const float green = (float)(0.5 + 0.5 + SDL_sin(now + SDL_PI_D * 2/3));
    const float blue = (float)(0.5 + 0.5 * SDL_sin(now + SDL_PI_D * 4/3));

    SDL_SetRenderDrawColorFloat(renderer, red, green, blue, SDL_ALPHA_OPAQUE_FLOAT);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void* appstate, SDL_AppResult result) {
    ;
}
