#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <conio.h>

#include "Texture.h"

#define WIDTH 800
#define HEIGHT 600
#define WINDOW_TITLE "WINDOW"

using namespace std;

SDL_Renderer *renderer = NULL;
SDL_Window *window = NULL;
Texture *player = NULL;

bool init();
void close();
bool loadTexture(SDL_Texture *&texture, string path);
bool loadMedia();

int main(int argc, char **argv) {
    if(!init()) {
        getch();
        return -1;
    }

    if(!loadMedia()) {
        close();
        getch();
        return -2;
    }

    SDL_Event e;

    bool quit = false;
    while(!quit) {

        while(SDL_PollEvent(&e) != 0) {
            if(e.type == SDL_QUIT)
                quit = true;
        }

        const Uint8* keys = SDL_GetKeyboardState(NULL);

        if(keys[SDL_SCANCODE_A]) {
            if(player->x > 0)
                player->x--;
        }
        if(keys[SDL_SCANCODE_D]) {
            if(player->x < WIDTH - player->width)
                player->x++;
        }
        if(keys[SDL_SCANCODE_W]) {
            if(player->y > 0)
                player->y--;
        }
        if(keys[SDL_SCANCODE_S]) {
            if(player->y < HEIGHT - player->height)
                player->y++;
        }
        if(keys[SDL_SCANCODE_ESCAPE])
            quit = true;
        if(keys[SDL_SCANCODE_R]) {

        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        player->render();

        SDL_RenderPresent(renderer);
    }

    close();
    return 0;
}

bool init() {
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Initialization error: %s", SDL_GetError());
        return false;
    }

    //should be freed if error occurs
    window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    if(!window) {
        printf("Window could not be created: %s", SDL_GetError());
        SDL_Quit();
        return false;
    }

    int flags = IMG_INIT_JPG | IMG_INIT_PNG;

    if(!(IMG_Init(flags) & flags)) {
        printf("SDL_image error: %s", IMG_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(!renderer) {
        printf("%s", SDL_GetError());
        SDL_DestroyWindow(window);
        IMG_Quit();
        SDL_Quit();
        return false;
    }

    return true;
}

void close() {
    player->destroy();
    player = NULL;

    SDL_DestroyWindow(window);
    window = NULL;

    SDL_DestroyRenderer(renderer);
    renderer = NULL;

    IMG_Quit();
    SDL_Quit();
}

bool loadMedia() {
    bool is_good = true;

    player = new Texture(30, 100, renderer);
    is_good = player->loadTexture("player.png") && is_good;

    return is_good;
}
