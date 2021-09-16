#include <stdio.h>
#include <string>
#include <SDL.h>

#define WIDTH 800
#define HEIGHT 600
#define WINDOW_TITLE "WINDOW"

using namespace std;

SDL_Window *window = NULL;
SDL_Surface *screen = NULL;
SDL_Surface *bmp = NULL;

bool loadBMP(SDL_Surface *&surface, string path) {
    surface = SDL_LoadBMP(path.c_str());
    if(!surface) {
        printf(SDL_GetError());
        return false;
    }

    return true;
}

bool init() {
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Initialization error: %s", SDL_GetError());
        return false;
    }

    window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    if(!window) {
        printf("Window could not be created: %s", SDL_GetError());
        SDL_Quit();
        return false;
    }
    screen = SDL_GetWindowSurface(window);

    return true;
}

void close() {
    SDL_FreeSurface(bmp);
    bmp = NULL;

    SDL_DestroyWindow(window);
    window = NULL;

    SDL_Quit();
}

bool loadMedia() {
    bool is_good = true;

    if(!loadBMP(bmp, "alamakota.bmp"))
        is_good = false;

    return is_good;
}

int main(int argc, char **argv) {
    if(!init())
        return -1;

    if(!loadMedia()) {
        close();
        return -2;
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
        if(keys[SDL_SCANCODE_ESCAPE])
            quit = true;

        SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 80 + colorShift, 180 - colorShift, 130 + colorShift));

        SDL_UpdateWindowSurface(window);
    }

    close();
    return 0;
}
