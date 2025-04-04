#ifndef TEXT_H_
#define TEXT_H_
#include "CommonFunc.h"

class Text {
public:
	Text();
	~Text();

	TTF_Font* loadFont(const char* path, int size);
	SDL_Texture* loadText(SDL_Renderer* renderer, const char* text, TTF_Font* font, SDL_Color textColor);
	void renderText(SDL_Renderer* renderer, SDL_Texture* texture, int x, int y);
};



#endif // !TEXT_H-
