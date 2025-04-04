
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
private:
};






#endif // !MUSIC_H_
