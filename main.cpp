#include <stdio.h>
#include <string>
#include <SDL.h>
#include <conio.h>

#define WIDTH 800
#define HEIGHT 600
#define WINDOW_TITLE "WINDOW"

using namespace std;

SDL_Window *window = NULL;
SDL_Surface *screen = NULL;
SDL_Surface *bmp = NULL;
SDL_Surface *square = NULL;
SDL_Surface *player = NULL;

bool init();
void close();
bool loadBMP(SDL_Surface *&surface, string path);
bool loadMedia();
bool scaleImage(SDL_Surface *&original, int newWidth, int newHeight);

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

    bool quit = false;
    while(!quit) {

        while(SDL_PollEvent(&e) != 0) {
            if(e.type == SDL_QUIT)
                quit = true;
        }

        int colorShift = 0;
        const Uint8* keys = SDL_GetKeyboardState(NULL);

        if(keys[SDL_SCANCODE_LEFT]) {
            colorShift -= 30;
            rec.x--;
        }
        if(keys[SDL_SCANCODE_RIGHT]) {
            colorShift += 65;
            rec.x++;
        }
        if(keys[SDL_SCANCODE_UP]) {
            colorShift -= 50;
            rec.y--;
        }
        if(keys[SDL_SCANCODE_DOWN]) {
            colorShift += 90;
            rec.y++;
        }
        if(keys[SDL_SCANCODE_ESCAPE])
            quit = true;

        SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 80, 180, 130));
        SDL_BlitSurface(player, NULL, screen, &rec);

        SDL_UpdateWindowSurface(window);
    }

    close();
    return 0;
}


bool loadBMP(SDL_Surface *&surface, string path) {
    surface = SDL_LoadBMP(path.c_str());
    if(!surface) {
        printf(SDL_GetError());
        return false;
    }
    SDL_Surface *optimized = SDL_ConvertSurface(surface, surface->format, 0);
    if(!optimized) {
        SDL_FreeSurface(surface);
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

    SDL_FreeSurface(square);
    square = NULL;

    SDL_FreeSurface(player);
    player = NULL;

    SDL_DestroyWindow(window);
    window = NULL;

    SDL_Quit();
}

bool loadMedia() {
    bool is_good = true;

    if(!loadBMP(bmp, "alamakota.bmp"))
        is_good = false;
    if(!loadBMP(player, "player.bmp"))
        is_good = false;
    if(!scaleImage(player,96,48))
        is_good=false;

    square = SDL_CreateRGBSurface(0, 40, 40, 32, 0, 0, 0, 0);
    SDL_FillRect(square, NULL, SDL_MapRGB(square->format, 40, 80, 120));

    return is_good;
}

bool scaleImage(SDL_Surface *&og, int newWidth, int newHeight) {
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

    if(SDL_BlitScaled(og, NULL, newImage, &rec)<0){
        SDL_FreeSurface(newImage);
        printf("Image could not be scaled: %s", SDL_GetError());
        return false;
    }

    SDL_FreeSurface(og);
    og = newImage;

    return true;
}
