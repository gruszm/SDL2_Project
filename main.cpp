#include <SDL.h>
#include <stdio.h>
#include <string>
#include <conio.h>

#include "Texture.h"

#define WIDTH 800
#define HEIGHT 600
#define WINDOW_TITLE "WINDOW"

SDL_Renderer *renderer = NULL;
SDL_Window *window = NULL;
TTF_Font *font = NULL;
Texture *textTexture = NULL;
Texture *playerTexture = NULL;

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
            if(playerTexture->getX() > 0)
                playerTexture->move(-10, 0);
        }
        if(keys[SDL_SCANCODE_D]) {
            if(playerTexture->getX() < WIDTH - playerTexture->getWidth())
                playerTexture->move(10, 0);
        }
        if(keys[SDL_SCANCODE_W]) {
            if(playerTexture->getY() > 0)
                playerTexture->move(0, -10);
        }
        if(keys[SDL_SCANCODE_S]) {
            if(playerTexture->getY() < HEIGHT - playerTexture->getHeight())
                playerTexture->move(0, 10);
        }
        if(keys[SDL_SCANCODE_ESCAPE])
            quit = true;

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        textTexture->render();
        playerTexture->render();

        SDL_RenderPresent(renderer);
    }

    close();
    return 0;
};

bool init() {
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Initialization error: %s", SDL_GetError());
        return false;
    }

    //should be freed if error occurs
    window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    if(!window) {
        printf("Window could not be created: %s", SDL_GetError());
        close();
        return false;
    }

    int flags = IMG_INIT_JPG | IMG_INIT_PNG;
    if(!(IMG_Init(flags) & flags)) {
        printf("SDL_image error: %s", IMG_GetError());
        close();
        return false;
    }

    if(TTF_Init() == -1) {
        printf("SDL_ttf error: %s", TTF_GetError());
        close();
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
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
    destroyTexture(playerTexture);
    destroyTexture(textTexture);

    TTF_CloseFont(font);
    font = NULL;

    SDL_DestroyWindow(window);
    window = NULL;

    SDL_DestroyRenderer(renderer);
    renderer = NULL;

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

bool loadMedia() {
    bool is_good = true;

    //to be placed elsewhere
    font = TTF_OpenFont("ITCKRIST.TTF", 28);
    if(!font) {
        printf("%s", TTF_GetError());
        is_good = false;
    }

    playerTexture = new Texture(30, 100, renderer);
    is_good = playerTexture->loadTexture("player.png") && is_good;

    if(is_good)
        playerTexture->setBlendMode(SDL_BLENDMODE_BLEND);

    if(is_good) {
        textTexture = new Texture(300, 300, renderer);

        SDL_Color color;
        color.r = 200;
        color.g = 120;
        color.b = 150;
        is_good = textTexture->createTextureFromText(font, "ALA MA KOTA", color) && is_good;
    }

    return is_good;
}
