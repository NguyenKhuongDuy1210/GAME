#include "Music.h"

Music::Music() {
	width_frame = 0;
	height_frame = 0;
	current_frame = 0;
	volumeTexture = NULL;
	volume = 128;
	frame_volume.resize(2, { 0, 0, 0, 0 });
	rect_volume = { 0, 0, 0, 0 };
	is_volume = 0;
}

Music::~Music() {

}

Mix_Music* Music::loadMusic(const char* path)
{
    Mix_Music* gMusic = Mix_LoadMUS(path);
    if (gMusic == nullptr) {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR,
            "Could not load music! SDL_mixer Error: %s", Mix_GetError());
    }
    return gMusic;
}

void Music::play(Mix_Music* gMusic)
{
    if (gMusic == nullptr) return;

    if (Mix_PlayingMusic() == 0) {
        Mix_PlayMusic(gMusic, -1);
    }
    else if (Mix_PausedMusic() == 1) {
        Mix_ResumeMusic();
    }
}

Mix_Chunk* Music::loadSound(const char* path) {
    Mix_Chunk* gChunk = Mix_LoadWAV(path);
    if (gChunk == nullptr) {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR,
            "Could not load sound! SDL_mixer Error: %s", Mix_GetError());
    }
	return gChunk;
}

void Music::play(Mix_Chunk* gChunk) {
    if (gChunk != nullptr) {
        Mix_PlayChannel(-1, gChunk, 0);
    }
}

void Music::loadImgVolume(SDL_Renderer* renderer) {
    SDL_Texture* new_texture = NULL;
    SDL_Rect rect = { 0,0,0,0 };
    SDL_Surface* load_surface = IMG_Load("music//volume.png");
    if (load_surface != NULL)
    {
        new_texture = SDL_CreateTextureFromSurface(renderer, load_surface);
        if (new_texture != NULL)
        {
            rect.w = load_surface->w;
            rect.h = load_surface->h;
        }
        SDL_FreeSurface(load_surface);
    }
    volumeTexture = new_texture;
    width_frame = rect.w / 2;
    height_frame = rect.h;
	rect_volume.x = 1150;
	rect_volume.y = 650;
	rect_volume.w = 40;
	rect_volume.h = 40;
}

void Music::setClipsVolume() {
    if (width_frame > 0 && height_frame > 0)
    {
        frame_volume.resize(2);
        for (int i = 0;i < 2;i++) {
            frame_volume[i].x = i * width_frame;
            frame_volume[i].y = 0;
            frame_volume[i].w = width_frame;
            frame_volume[i].h = height_frame;
        }
    }
}

void Music::renderVolume(SDL_Renderer* renderer) {
	SDL_Rect currentClip = frame_volume[current_frame];
	SDL_RenderCopy(renderer, volumeTexture, &currentClip, &rect_volume);
}

void Music::updateVolume(const bool is_click, int mouseX, int mouseY) {
	if (is_click && IsMouseOver(mouseX, mouseY)) {
		if (current_frame == 0) {
			current_frame = 1;
            volume = 0;
		}
		else {
			current_frame = 0;
            volume = VOLUME_MUSIC;
		}
	}
}

bool Music::IsMouseOver(int mouseX, int mouseY) {
    return mouseX >= rect_volume.x && mouseX <= rect_volume.x + rect_volume.w &&
        mouseY >= rect_volume.y && mouseY <= rect_volume.y + rect_volume.h;
}


