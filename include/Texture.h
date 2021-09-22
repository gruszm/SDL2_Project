#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL.h>
#include <SDL_image.h>
#include <string>

using namespace std;

class Texture {
public:
    Texture(int x, int y, SDL_Renderer *renderer);
    virtual ~Texture();

    void move(int x, int y);

    //tools
    bool loadTexture(string path);
    void render();
    void destroy();
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
    int x, y; //destroy(): should be set to 0
    int width, height; //destroy(): should be set to 0
    Uint8 alphaValue;
    SDL_Texture *sdl_texture; //destroy(): should be destroyed
    SDL_Renderer *renderer; //destroy(): should be NULLed
};

#endif // TEXTURE_H
