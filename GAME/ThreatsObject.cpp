
#include "ThreatsObject.h"

ThreatsObject::ThreatsObject()
{
	rect_threat = { 0, 0, 0, 0 };
	texture_threat = NULL;
	x_val = 0.0;
	y_val = 0.0;
	x_pos = 0.0;
	y_pos = 0.0;
	frame = 0;
	width_frame = 0;
	height_frame = 0;
	for (int i = 0; i < 8; ++i)
	{
		frame_clips[i] = { 0, 0, width_frame, height_frame };
	}
	last_shot_time = 0;
	shot_delay = 0;    
	bullets_in_shot = 5;  
	current_bullets = 0;  

	m_is_active = true;
}

ThreatsObject::~ThreatsObject()
{
	Free_Threat();
}

bool ThreatsObject::LoadImg_Threats(const char* path, SDL_Renderer* renderer, int frame_number)
{
	SDL_Texture* new_texture = NULL;
	SDL_Surface* load_surface = IMG_Load(path);
	if (load_surface != NULL)
	{
		new_texture = SDL_CreateTextureFromSurface(renderer, load_surface);
		if (new_texture != NULL)
		{
			rect_threat.w = load_surface->w;
			rect_threat.h = load_surface->h;
		}
		SDL_FreeSurface(load_surface);
	}
	texture_threat = new_texture;

	width_frame = rect_threat.w / frame_number;
	height_frame = rect_threat.h;

	return texture_threat != NULL;
}

void ThreatsObject::set_clips_threats(int frame_number)
{
	if (width_frame > 0 && height_frame > 0)
	{
		for (int i = 0;i < frame_number;i++) {
			frame_clips[i].x = i * width_frame;
			frame_clips[i].y = 0;
			frame_clips[i].w = width_frame;
			frame_clips[i].h = height_frame;
		}
	}
}

void ThreatsObject::Show_threats(SDL_Renderer* renderer, int frame_number) {
    frame++;
    if (frame >= frame_number) frame = 0;
    SDL_Rect* current_clip = &frame_clips[frame];
    SDL_Rect renderQuad = { static_cast<int>(x_pos), static_cast<int>(y_pos), width_frame, height_frame };
    SDL_RenderCopy(renderer, texture_threat, current_clip, &renderQuad);
}



void ThreatsObject::Init_Bullet(SDL_Renderer* renderer,const int& x_, const int& y_, const int& xVal, const int& yVal) {
	Uint32 current_time = SDL_GetTicks();
		BulletObject* t_bullet = new BulletObject();
		bool ret = t_bullet->loadImg_Bullet(renderer, "threats//bullletThreats.png", 1);
		if (!ret) {
			cout << "Failed to load bullet image: " << SDL_GetError() << endl;
			delete t_bullet; 
			return;
		}
		t_bullet->setCLip_Bullet(1);
		t_bullet->setRect_Bullet(x_pos + x_, y_pos + y_);

		switch (current_bullets) {
		case 0: 
			t_bullet->set_x_val(xVal);
			t_bullet->set_y_val(0);
			break;
		case 1: 
			t_bullet->set_x_val(xVal);
			t_bullet->set_y_val(-yVal / 2);
			break;
		case 2:
			t_bullet->set_x_val(xVal);
			t_bullet->set_y_val(-yVal);
			break;
		case 3:
			t_bullet->set_x_val(xVal);
			t_bullet->set_y_val(yVal / 2);
			break;
		case 4:
			t_bullet->set_x_val(xVal);
			t_bullet->set_y_val(yVal);
			break;
		}

		t_bullet->set_is_move(true);
		t_bullet_list.push_back(t_bullet);

		current_bullets++; 
}

void ThreatsObject::make_Bullet_Threats(SDL_Renderer* renderer, const int& x_limit, const int& y_limit) {
	for (int i = 0; i < t_bullet_list.size(); i++) {
		BulletObject* t_bullet = t_bullet_list.at(i);
		if (t_bullet != NULL) {
			if (t_bullet->get_is_move()) {
				t_bullet->HandleMove(x_limit, y_limit);
				SDL_Rect rect_bullet = { t_bullet->get_bullet_x_pos(), t_bullet->get_bullet_y_pos(), 20, 15 };
				int frame_bullet = 0;
				t_bullet->Render_Bullet(renderer, rect_bullet, frame_bullet);
			}
			else {
				t_bullet_list.erase(t_bullet_list.begin() + i);
				delete t_bullet;
				t_bullet = NULL;
				i--;
			}
		}
	}
}

void ThreatsObject::EraseBullet(const int idx)
{
	int size = t_bullet_list.size();
	if (size > 0 && idx < size)
	{
		BulletObject* p_bullet = t_bullet_list.at(idx);
		t_bullet_list.erase(t_bullet_list.begin() + idx);
		if (p_bullet != NULL)
		{
			delete p_bullet;
			p_bullet = NULL;
		}
	}
}

void ThreatsObject::ShowBullet(SDL_Renderer* renderer, const int& x_, const int& y_, const int& xVal, const int& yVal) {
	Uint32 current_time = SDL_GetTicks();
	shot_delay = 1000;
	if (current_time - last_shot_time >= shot_delay) {
		current_bullets = 0; 
		last_shot_time = current_time;
	}

	if (current_bullets < bullets_in_shot) {
		Init_Bullet(renderer, x_, y_, xVal, yVal);
	}

	make_Bullet_Threats(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
}

bool ThreatsObject::is_active() const {
	// Kiểm tra điều kiện để threat được coi là "active":
	// 1. Vẫn trong màn hình
	// 2. Chưa bị tiêu diệt
	return m_is_active &&
		(get_x_pos() < SCREEN_WIDTH) &&
		(get_y_pos() < SCREEN_HEIGHT);
}

void ThreatsObject::set_active(bool active) {
	m_is_active = active;
}

void ThreatsObject::Free_Threat()
{
	if (texture_threat == NULL)
	{
		SDL_DestroyTexture(texture_threat);
		texture_threat = NULL;
		rect_threat.w = 0;
		rect_threat.h = 0;
	}
}
