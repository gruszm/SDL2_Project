#include "Texture.h"

Texture::Texture(int x, int y, SDL_Renderer *renderer)
    :
    x(x),
    y(y),
    alphaValue(255),
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

void Texture::move(int x, int y) {
    this->x += x;
    this->y += y;
}

void Texture::setColorMod(Uint8 r, Uint8 g, Uint8 b) {
    SDL_SetTextureColorMod(this->sdl_texture, r, g, b);
}

void Texture::setBlendMode(SDL_BlendMode blendMode) {
    SDL_SetTextureBlendMode(this->sdl_texture, blendMode);
}

void Texture::setAlpha(int alpha) {
    Uint8 finalAlpha = 255;

    if(alpha > 255)
        finalAlpha = 255;
    else if(alpha < 0)
        finalAlpha = 0;
    else
        finalAlpha = alpha;

    this->alphaValue = finalAlpha;
    SDL_SetTextureAlphaMod(this->sdl_texture, finalAlpha);
}

Uint8 Texture::getAlpha() {
    return this->alphaValue;
}

//getters and setters for variables

int Texture::getX() {
    return x;
}

int Texture::getY() {
    return y;
}

int Texture::getWidth() {
    return width;
}

int Texture::getHeight() {
    return height;
}
