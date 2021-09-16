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

    SDL_Rect rec;
    rec.x=40;
    rec.y=60;
    rec.w=400;
    rec.h=300;
    SDL_FillRect(surf,&rec,SDL_MapRGB(surf->format,20,120,50));
    SDL_UpdateWindowSurface(window);

    SDL_Delay(2000);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
