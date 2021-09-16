#include <stdio.h>
#include <SDL.h>

#define WIDTH 800
#define HEIGHT 600

using namespace std;

int main(int argc, char **argv) {
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Initialization error: %s", SDL_GetError());
        return 0;
    }

    SDL_Window *window = SDL_CreateWindow("WINDOW", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_ALWAYS_ON_TOP);
    if(!window) {
        printf("window error");
        SDL_Quit();
        return 0;
    }

    SDL_Surface *surf = SDL_GetWindowSurface(window);
    if(!surf) {
        printf("surface error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 0;
    }

    SDL_Event e;

    bool quit = false;
    while(!quit) {
        while(SDL_PollEvent(&e) != 0) {
            if(e.type == SDL_QUIT)
                quit = true;
        }

        int colorShift = 0;

        const Uint8* keys = SDL_GetKeyboardState(NULL);
        if(keys[SDL_SCANCODE_LEFT])
            colorShift -= 30;
        if(keys[SDL_SCANCODE_RIGHT])
            colorShift += 65;
        if(keys[SDL_SCANCODE_UP])
            colorShift -= 50;
        if(keys[SDL_SCANCODE_DOWN])
            colorShift += 90;

        SDL_FillRect(surf, NULL, SDL_MapRGB(surf->format, 70 + colorShift, 120 + colorShift, 50 + colorShift));

        SDL_UpdateWindowSurface(window);
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
