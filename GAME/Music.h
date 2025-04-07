
#ifndef MUSIC_H_
#define MUSIC_H_

#include "CommonFunc.h"

class Music
{
public:
	Music();
	~Music();

	Mix_Music* loadMusic(const char* path);
	void play(Mix_Music* gMusic);

	Mix_Chunk* loadSound(const char* path);
	void play(Mix_Chunk* gChunk);

	void loadImgVolume(SDL_Renderer* renderer);
	void setClipsVolume();
	int getVolume() { return volume; }
	void renderVolume(SDL_Renderer* renderer);
	void updateVolume(const bool is_click, int mouseX, int mouseY);
	bool IsMouseOver(int mouseX, int mouseY);

private:
	int volume;
	vector <SDL_Rect> frame_volume;
	SDL_Texture* volumeTexture;
	SDL_Rect rect_volume;
	int width_frame;
	int height_frame;
	int current_frame;
	int is_volume;
};






#endif // !MUSIC_H_
