#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL.h>
#include <SDL_image.h>
#include <string>

using namespace std;

class Texture {
public:
    int x, y; //destroy(): should be set to 0
    int width, height; //destroy(): should be set to 0

    Texture(int x, int y, SDL_Renderer *renderer);
    virtual ~Texture();

    bool loadTexture(string path);
    void render();
    void destroy();
    void move(int x, int y);

protected:

private:
    SDL_Texture *sdl_texture; //destroy(): should be destroyed
    SDL_Renderer *renderer; //destroy(): should be NULLed
};

#endif // TEXTURE_H
