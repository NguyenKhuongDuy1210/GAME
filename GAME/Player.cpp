
#include "Player.h"

Player::Player()
{
	texture_player = NULL;
	width_frame1 = 0;
	height_frame1 = 0;
	frame_clips_player1.resize(7, { 0, 0, width_frame1, height_frame1 });

	texture = NULL;
	width_frame2 = 0;
	height_frame2 = 0;
	frame_clips_player2.resize(2, { 0, 0, width_frame2, height_frame2 });

	texture_die = NULL;
	width_frame3 = 0;
	height_frame3 = 0;
	frame_clips_player3.resize(14, { 0, 0, width_frame3, height_frame3 });

	x = 20;
	y = 100;
	x_val = 0;
	y_val = 0;
	
	frame_bullet = 0;
	frame_tail = 0;
	frame_player = 3;
	frame_die = 0;
	last_shot_time = 0;
}

Player::~Player()
{
	if (texture_player == NULL) {
		SDL_DestroyTexture(texture_player);
	}
	if (texture == NULL) {
		SDL_DestroyTexture(texture);
	}
	if (texture_die == NULL) {
		SDL_DestroyTexture(texture);
	}
}

// phần thân player
void Player::LoadImg_Player(SDL_Renderer* renderer)
{
	SDL_Texture* new_texture = NULL;
	SDL_Rect rect = { 0, 0, 0, 0 };
	SDL_Surface* load_surface = IMG_Load("player//player1.png");
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
	texture_player = new_texture;

	width_frame1 = rect.w / 7;
	height_frame1 = rect.h;
}
void Player::Set_Clips_Player() {
	if (width_frame1 > 0 && height_frame1 > 0)
	{
		for (int i = 0;i < 7;i++) {
			frame_clips_player1[i].x = i * width_frame1;
			frame_clips_player1[i].y = 0;
			frame_clips_player1[i].w = width_frame1;
			frame_clips_player1[i].h = height_frame1;
		}
	}
}

// phần đuôi player
void Player::LoadImg_Tail(SDL_Renderer* renderer, const char* path, const int frame_number) {
	SDL_Texture* new_texture = NULL;
	SDL_Rect rect = { 0, 0, 0, 0 };
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

	width_frame2 = rect.w / frame_number;
	height_frame2 = rect.h;
}
void Player::Set_Clips(int frame_number) {
	if (width_frame2 > 0 && height_frame2 > 0)
	{
		for (int i = 0;i < frame_number;i++) {
			frame_clips_player2[i].x = i * width_frame2;
			frame_clips_player2[i].y = 0;
			frame_clips_player2[i].w = width_frame2;
			frame_clips_player2[i].h = height_frame2;
		}
	}
}

// phần mạng player
void Player::LoadImg_Die(SDL_Renderer* renderer) {
	SDL_Texture* new_texture = NULL;
	SDL_Rect rect = { 0, 0, 0, 0 };
	SDL_Surface* load_surface = IMG_Load("player//numdie.png");
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
	else {
		cout << "Load Img numdie is " << IMG_GetError() << endl;
	}
	texture_die = new_texture;

	width_frame3 = rect.w / 14;
	height_frame3 = rect.h;
}
void Player::Set_Clips_Die() {
	if (width_frame3 > 0 && height_frame3 > 0)
	{
		for (int i = 0;i < 14;i++) {
			frame_clips_player3[i].x = i * width_frame3;
			frame_clips_player3[i].y = 0;
			frame_clips_player3[i].w = width_frame3;
			frame_clips_player3[i].h = height_frame3;
		}
	}
}


void Player::HandleInputAction(SDL_Event events, SDL_Renderer* renderer, Mix_Chunk* sound_bullet)
{
	BulletObject* p_bullet = NULL;
	if (events.type == SDL_MOUSEBUTTONDOWN) {
		if (events.button.button == SDL_BUTTON_LEFT) {
			// Tạo đạn khi nhấn chuột lần đầu
			BulletObject* p_bullet = new BulletObject();
			if (p_bullet->loadImg_Bullet(renderer, "player//laser_bullet.png", 2)) {
				p_bullet->setCLip_Bullet(2);
				p_bullet->setRect_Bullet(x + 110, y + 25);
				p_bullet->set_x_val(20);
				p_bullet->set_y_val(0);
				p_bullet->set_is_move(true);
			}
			p_bullet_list.push_back(p_bullet);
			sound.play(sound_bullet);
			last_shot_time = SDL_GetTicks(); // Cập nhật thời gian lần cuối bắn đạn
		}
		
	}
	if (events.type == SDL_KEYDOWN)
	{
		switch (events.key.keysym.sym)
		{
		case SDLK_d:
			LoadImg_Tail(renderer, "player//04.png", 2);
			Set_Clips(2);
			x_val = 12;
			y_val = 0;
			break;
		case SDLK_a:
			x_val = -12;
			y_val = 0;
			break;
		case SDLK_w:
			frame_player++;
			if (frame_player >= 7) frame_player = 6;
			x_val = 0;
			y_val = -12;
			break;
		case SDLK_s:
			frame_player--;
			if (frame_player <= 0) frame_player = 0;
			x_val = 0;
			y_val = 12;
			break;
		default:
			break;
		}
	}
	else if (events.type == SDL_KEYUP)
	{
		switch (events.key.keysym.sym)
		{
		case SDLK_d:
			LoadImg_Tail(renderer, "player//02.png", 2);
			Set_Clips(2);
			x_val = 0;
			break;
		case SDLK_a:
			x_val = 0;
			break;
		case SDLK_w:
			frame_player = 3;
			y_val = 0;
			break;
		case SDLK_s:
			frame_player = 3;
			y_val = 0;
			break;
		default:
			break;
		}
	}
}

void Player::HandleContinuousShooting(SDL_Renderer* renderer, Mix_Chunk* sound_bullet) {
	Uint32 mouse_state = SDL_GetMouseState(NULL, NULL);
	// Kiểm tra nếu chuột phải đang được giữ và đã đủ thời gian trễ
	if ((mouse_state & SDL_BUTTON(SDL_BUTTON_LEFT))) {
		Uint32 current_time = SDL_GetTicks();
		shot_delay = 100;
		if (current_time - last_shot_time > shot_delay) {
			// Tạo đạn mới
			BulletObject* p_bullet = new BulletObject();
			if (p_bullet->loadImg_Bullet(renderer, "player//laser_bullet.png", 2)) {
				p_bullet->setCLip_Bullet(2);
				p_bullet->setRect_Bullet(x + 110, y + 25);
				p_bullet->set_x_val(20);
				p_bullet->set_y_val(0);
				p_bullet->set_is_move(true);
			}
			p_bullet_list.push_back(p_bullet);
			sound.play(sound_bullet);
			last_shot_time = current_time; // Cập nhật thời gian lần cuối bắn đạn
		}
	}
}

void Player::HandleBullet(SDL_Renderer* renderer)
{
	for (int i = 0; i < p_bullet_list.size(); i++)
	{
		BulletObject* p_bullet = p_bullet_list.at(i);
		if (p_bullet != NULL)
		{
			if (p_bullet->get_is_move())
			{
				p_bullet->HandleMove(SCREEN_WIDTH, SCREEN_HEIGHT);
				SDL_Rect rect2 = { p_bullet->get_bullet_x_pos(), p_bullet->get_bullet_y_pos(), 40, 20 };
				frame_bullet++;
				if (frame_bullet >= 2) frame_bullet = 0;
				p_bullet->Render_Bullet(renderer, rect2, frame_bullet);
			}
			else
			{
				p_bullet_list.erase(p_bullet_list.begin() + i);
				if (p_bullet != NULL)
				{
					delete p_bullet;
					p_bullet = NULL;
				}
			}
		}
	}
}

void Player::EraseBullet(const int idx)
{
	int size = p_bullet_list.size();
	if (size > 0 && idx < size)
	{
		BulletObject* p_bullet = p_bullet_list.at(idx);
		p_bullet_list.erase(p_bullet_list.begin() + idx);
		if (p_bullet != NULL)
		{
			delete p_bullet;
			p_bullet = NULL;
		}
	}
}

void Player::UpdatePlayer()
{
	if (x > 1050) x = 1050;
	if (x < 0) x = 0;
	if (y > 640) y = 640;
	if (y < 0) y = 0;
	x += x_val;
	y += y_val;
}


void Player::RenderPlayer(SDL_Renderer* renderer)
{
	SDL_Rect rect_player = { x, y, 160, 60 };
	SDL_Rect current_clip = frame_clips_player1[frame_player];
	SDL_RenderCopy(renderer, texture_player, &current_clip, &rect_player);

	SDL_Rect rect1 = { x - 12, y + 22, 32, 16 };
	frame_tail++;
	if (frame_tail >= 2) frame_tail = 0;
	SDL_Rect current_clip1 = frame_clips_player2[frame_tail];
	SDL_RenderCopy(renderer, texture, &current_clip1, &rect1);
		
	SDL_Rect rect_die = { 20, 660, 200, 40 };
	if (frame_die >= 14) { frame_die = 13; }
	SDL_Rect current_clip2 = frame_clips_player3[frame_die];
	SDL_RenderCopy(renderer, texture_die, &current_clip2, &rect_die);

// đạn
	HandleBullet(renderer);
}

