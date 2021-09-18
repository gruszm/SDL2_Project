#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <conio.h>

#define WIDTH 800
#define HEIGHT 600
#define WINDOW_TITLE "WINDOW"

using namespace std;

SDL_Renderer *renderer = NULL;
SDL_Window *window = NULL;
SDL_Texture *bmp = NULL;
SDL_Texture *player = NULL;

bool init();
void close();
bool loadTexture(SDL_Texture *&texture, string path);
bool loadMedia();
bool scaleSurface(SDL_Surface *&original, int newWidth, int newHeight);

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

    SDL_Rect rec;
    rec.x = 40;
    rec.y = 40;
    rec.w = 48;
    rec.h = 96;

    bool quit = false;
    while(!quit) {

        while(SDL_PollEvent(&e) != 0) {
            if(e.type == SDL_QUIT)
                quit = true;
        }

        const Uint8* keys = SDL_GetKeyboardState(NULL);

        if(keys[SDL_SCANCODE_LEFT]) {
            rec.x--;
        }
        if(keys[SDL_SCANCODE_RIGHT]) {
            rec.x++;
        }
        if(keys[SDL_SCANCODE_UP]) {
            rec.y--;
        }
        if(keys[SDL_SCANCODE_DOWN]) {
            rec.y++;
        }
        if(keys[SDL_SCANCODE_ESCAPE])
            quit = true;

        SDL_RenderClear(renderer);

        SDL_RenderCopy(renderer, player, NULL, &rec);

        SDL_RenderPresent(renderer);
    }

    close();
    return 0;
}


bool loadTexture(SDL_Texture *&texture, string path) {
    SDL_Surface *surface = IMG_Load(path.c_str()); //should be freed on error

    if(!surface) {
        printf("%s", IMG_GetError());
        return false;
    }

    SDL_Texture *temp = SDL_CreateTextureFromSurface(renderer, surface);

    if(!temp) {
        SDL_FreeSurface(surface);
        printf("%s", SDL_GetError());
        return false;
    }

    texture = temp;
    return true;
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

    SDL_SetRenderDrawColor(renderer, 255,255,255,255);

    return true;
}

void close() {
    SDL_DestroyTexture(bmp);
    bmp = NULL;

    SDL_DestroyTexture(player);
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

    if(!loadTexture(bmp, "alamakota.bmp"))
        is_good = false;
    if(!loadTexture(player, "player.bmp"))
        is_good = false;

    return is_good;
}

bool scaleSurface(SDL_Surface *&og, int newWidth, int newHeight) {
    SDL_Surface *newImage = SDL_CreateRGBSurface(0, newWidth, newHeight, 32, og->format->Rmask, og->format->Gmask, og->format->Bmask, og->format->Amask);

    if(!newImage) {
        printf("Image could not be scaled: %s", SDL_GetError());
        return false;
    }

    SDL_Rect rec;
    rec.x = 0;
    rec.y = 0;
    rec.w = newWidth;
    rec.h = newHeight;

    if(SDL_BlitScaled(og, NULL, newImage, &rec) < 0) {
        SDL_FreeSurface(newImage);
        printf("Image could not be scaled: %s", SDL_GetError());
        return false;
    }

    SDL_FreeSurface(og);
    og = newImage;

    return true;
}
