
#include "MoveBackground.h"

MoveBackground::MoveBackground() 
{
    rects.resize(10, { 0,0,BACKGROUND_WIDTH, BACKGROUND_HEIGTH });
}

MoveBackground::~MoveBackground()
{
    clear();
}

vector<SDL_Texture*>  MoveBackground::loadLayerBackground(SDL_Renderer* renderer, const vector<const char*>& imagePaths)
{
    textures.clear();
    for (size_t i = 0; i < imagePaths.size(); ++i) {
        SDL_Texture* new_texture;
        SDL_Rect rect1 = { 0, 0, 0, 0 };
        SDL_Surface* load_surface = IMG_Load(imagePaths[i]);
        if (load_surface != NULL)
        {
            new_texture = SDL_CreateTextureFromSurface(renderer, load_surface);
            if (new_texture == nullptr) {
                cout << SDL_GetError() << endl;
            }
            else {
                rect1.w = load_surface->w;
                rect1.h = load_surface->h;
            }
            SDL_FreeSurface(load_surface);
        }
        else
        {
            cout << IMG_GetError() << endl;;
        }
        textures.push_back(new_texture);
    }
    return textures;
}

void MoveBackground::update() {
    for (size_t i = 0; i < textures.size() && i < speeds.size(); ++i) {
        rects[i].x -= speeds[i];
       if (rects[i].x + rects[i].w <= 0) {
            rects[i].x = 0;
        }
    }
}

void MoveBackground::RenderBackground(SDL_Renderer* renderer) {
    
    for (size_t i = 0; i < textures.size() && i < rects.size(); i++) {
        SDL_Rect rectquad = { getX(static_cast<int>(i)) + BACKGROUND_WIDTH, 0 , BACKGROUND_WIDTH, BACKGROUND_HEIGTH };
        SDL_RenderCopy(renderer, textures[i], NULL, &rects[i]);
        SDL_RenderCopy(renderer, textures[i], NULL, &rectquad);
            
    }
}

int MoveBackground::getX(int i) const {
    return (i >= 0 && i < rects.size()) ? rects[i].x : 0;
}

void MoveBackground::clear() {
    for (auto& texture : textures) {
        if (texture == NULL) {
            SDL_DestroyTexture(texture);
        }
    }
    textures.clear();
    rects.clear();
    speeds.clear();
}
