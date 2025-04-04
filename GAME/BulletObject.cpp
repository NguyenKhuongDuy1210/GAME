
#include "BulletObject.h"

BulletObject::BulletObject()
{
	Texture_Bullet = NULL;
	rect_bullet = { 0, 0, 0, 0 };
	width_frame = 0;
	height_frame = 0;
	frame_clips_bullet.resize(2, { 0, 0, width_frame, height_frame });
	frame = 0;



	x_val = 0;
	y_val = 0;
	is_move = false;
}

BulletObject::~BulletObject()
{

}

bool BulletObject::loadImg_Bullet(SDL_Renderer* renderer, const char* path, int frame_number)
{
	// Tải ảnh và tạo texture
	SDL_Texture* new_texture = NULL;

	SDL_Surface* load_surface = IMG_Load(path);
	if (load_surface != NULL)
	{
		new_texture = SDL_CreateTextureFromSurface(renderer, load_surface);
		if (new_texture != NULL)
		{
			rect_bullet.w = load_surface->w;
			rect_bullet.h = load_surface->h;
		}
		SDL_FreeSurface(load_surface);
	}
	Texture_Bullet = new_texture;

	width_frame = rect_bullet.w / frame_number;
	height_frame = rect_bullet.h;

	return Texture_Bullet != NULL;
}

void BulletObject::setCLip_Bullet(const int frame_number)
{
	if (width_frame > 0 && height_frame > 0)
	{
		for (int i = 0;i < frame_number;i++) {
			frame_clips_bullet[i].x = i * width_frame;
			frame_clips_bullet[i].y = 0;
			frame_clips_bullet[i].w = width_frame;
			frame_clips_bullet[i].h = height_frame;
		}
	}
}

void BulletObject::Render_Bullet(SDL_Renderer* renderer, SDL_Rect rectquad, int& frame1)
{
	frame = frame1;
	SDL_Rect current_clip = frame_clips_bullet[frame];
	SDL_RenderCopy(renderer, Texture_Bullet, &current_clip, &rectquad);
}

void BulletObject::setRect_Bullet(const int& x, const int&y) { 
	rect_bullet.x = x;
	rect_bullet.y = y;
}


void BulletObject::HandleMove(const int& x_border, const int& y_border)
{
	rect_bullet.x += x_val;
	rect_bullet.y += y_val;
	if (rect_bullet.x < 0 || rect_bullet.x > SCREEN_WIDTH || 
		rect_bullet.y < 0 || rect_bullet.y > SCREEN_HEIGHT)
	{
		is_move = false;
	}
}
