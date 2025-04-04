
#ifndef MOVE_BACKGROUND_H_
#define MOVE_BACKGROUND_H_

#include "CommonFunc.h"

class MoveBackground
{
public:
	MoveBackground();
	~MoveBackground();
	vector <SDL_Texture*> loadLayerBackground(SDL_Renderer* renderer, const vector<const char*>& imagePaths);
	void update();
	void RenderBackground(SDL_Renderer* renderer);
	int getX(int i) const;
	void setSpeeds(const vector<int>& newSpeeds) {
		speeds = newSpeeds;
	}
	void clear();
private:
	vector <int> speeds; 
	vector <SDL_Texture*> textures;
	vector <SDL_Rect> rects;
};


#endif // !MOVE_BACKGROUND_H_

