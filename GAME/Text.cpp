#include "Text.h"

Text::Text() {

}

Text::~Text() {
	
}

TTF_Font* Text::loadFont(const char* path, int size)
{
	TTF_Font* gFont = TTF_OpenFont(path, size);
	if (gFont == nullptr) {
		SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,
			SDL_LOG_PRIORITY_ERROR,
			"Load font %s", TTF_GetError());
	}
	return gFont;
}

SDL_Texture* Text::loadText(SDL_Renderer* renderer, const char* text, TTF_Font* font, SDL_Color textColor) {
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, text, textColor);
	if (textSurface == nullptr) {
		cout << "Render text surface %s" << TTF_GetError();
		return nullptr;
	}
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, textSurface);
	if (texture == nullptr) {
		cout << "Create texture from text %s" << SDL_GetError();
	}
	SDL_FreeSurface(textSurface);
	return texture;
}

void Text::renderText(SDL_Renderer* renderer, SDL_Texture* texture, int x, int y) {
	SDL_Rect renderQuad = { x, y, 0, 0 };
	SDL_QueryTexture(texture, NULL, NULL, &renderQuad.w, &renderQuad.h);
	SDL_RenderCopy(renderer, texture, NULL, &renderQuad);
}
