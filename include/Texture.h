#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>

using namespace std;

class Texture {
    friend void destroyTexture(Texture *&t);

public:
    Texture(int x, int y, SDL_Renderer *renderer);
    virtual ~Texture();

    void move(int x, int y);

    //tools
    bool loadTexture(string path);
    bool createTextureFromText(TTF_Font *font, string text, SDL_Color color);
    void render();
    void setColorMod(Uint8 r, Uint8 g, Uint8 b);
    void setBlendMode(SDL_BlendMode blendMode);
    void setAlpha(int alpha);
    Uint8 getAlpha();

    //getters and setters for variables
    int getX();
    int getY();
    int getWidth();
    int getHeight();

protected:

private:
    int x, y;
    int width, height;
    Uint8 alphaValue;
    SDL_Texture *sdl_texture; //free(): should be destroyed
    SDL_Renderer *renderer;
    void freeTexture(); //free texture if allocated
    void destroy();
};

void destroyTexture(Texture *&t);

#endif // TEXTURE_H
