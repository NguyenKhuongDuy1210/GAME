#include "Explosion.h"

Explosion::Explosion() {
	frame = 0;
	width_frame = 0;
	height_frame = 0;
	frame_clips.resize(7, {0, 0, 0, 0});
	texture = NULL;
	last_time = 0;
	is_explosion = 0;
	exp_x = 0;
	exp_y = 0;
}

Explosion::~Explosion() {
	if (texture != NULL) {
		SDL_DestroyTexture(texture);
		texture = NULL;
	}
}

bool Explosion::LoadImg_Explosion(SDL_Renderer* renderer, const char* path){
	SDL_Texture* new_texture = NULL;

	SDL_Rect rect = { 0,0,0,0 };
	SDL_Surface* load_surface = IMG_Load(path);
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
	texture = new_texture;

	width_frame = rect.w / 7;
	height_frame = rect.h;
	return texture != NULL;
}

void Explosion::Set_CLips_Expolsion() {
	if (width_frame > 0 && height_frame > 0)
	{
		frame_clips.resize(7);
		for (int i = 0;i < 7;i++) {
			frame_clips[i].x = i * width_frame;
			frame_clips[i].y = 0;
			frame_clips[i].w = width_frame;
			frame_clips[i].h = height_frame;
		}
	}
}

void Explosion::Show_Explosion(SDL_Renderer* renderer) {
	if (is_explosion) {
		Uint32 current_time = SDL_GetTicks();

		if (current_time - last_time > 70) {
			frame++;
			if (frame >= 7) { 
				frame = 0; 
				set_is_explosion(false, exp_x, exp_y); 
			}
			
			last_time = current_time; 
		}
		SDL_Rect rectquad = { exp_x, exp_y, 200, 150 };
		SDL_Rect current_clip = frame_clips[frame];
		SDL_RenderCopy(renderer, texture, &current_clip, &rectquad);
	}
}
