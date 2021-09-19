#include "Texture.h"

Texture::Texture(int x, int y, SDL_Renderer *renderer)
    :
    x(x),
    y(y),
    renderer(renderer) {

}

Texture::~Texture() {
    //dtor
}

bool Texture::loadTexture(string path) {
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

    width = surface->w;
    height = surface->h;

    SDL_FreeSurface(surface);

    sdl_texture = temp;
    return true;
}

void Texture::render() {
    SDL_Rect rec = {x, y, width, height};
    SDL_RenderCopy(renderer, sdl_texture, NULL, &rec);
}

void Texture::destroy() {
    width = 0;
    height = 0;

    SDL_DestroyTexture(sdl_texture);
    sdl_texture = NULL;

    renderer = NULL;

    delete this;
}
