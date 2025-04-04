
#ifndef PLAYER_H_
#define	PLAYER_H_

#include "CommonFunc.h"
#include "BulletObject.h"
#include "Music.h"

class Player
{
public:
	Player();
	~Player();
	// hinhh ảnh player
	void LoadImg_Player(SDL_Renderer* renderer);
	void Set_Clips_Player();
	void Set_frame_player(const int frame_player_) { frame_player = frame_player_; }

	// hình ảnh đuôi player
	void LoadImg_Tail(SDL_Renderer* renderer, const char* path, const int frame_number);
	void Set_Clips(const int frame_number);

	// hình ảnh mạng player
	void LoadImg_Die(SDL_Renderer* renderer);
	void Set_Clips_Die();
	void Set_Frame_Die(int& numdie) { frame_die = numdie; }




	void HandleInputAction(SDL_Event events, SDL_Renderer* renderer, Mix_Chunk* sound_bullet);
	void UpdatePlayer();
	void RenderPlayer(SDL_Renderer* renderer);
	void Set_Rect_Player(int x_start, int y_start) { x = x_start; y = y_start; }
	void Set_x_val(const int x_val_) { x_val = x_val_; }
	void Set_y_val(const int y_val_) { y_val = y_val_; }

	int get_x() const { return x; }
	int get_y() const { return y; }

	vector <BulletObject*> get_bullet_list() const { return p_bullet_list; }
	void HandleBullet(SDL_Renderer* renderer);
	void EraseBullet(const int idx);
	void HandleContinuousShooting(SDL_Renderer* renderer, Mix_Chunk* sound_bullet);

private:
	// dùng cho player
	SDL_Texture* texture_player;
	int width_frame1;
	int height_frame1;
	vector <SDL_Rect> frame_clips_player1;

	// dùng cho đuôi player
	SDL_Texture* texture;
	int width_frame2;
	int height_frame2;
	vector <SDL_Rect> frame_clips_player2;

	//
	SDL_Texture* texture_die;
	int width_frame3;
	int height_frame3;
	vector <SDL_Rect> frame_clips_player3;

	Uint32 last_shot_time; // Thời gian lần cuối bắn đạn
	Uint32 shot_delay = 100; // Thời gian trễ giữa các lần bắn (ms)

	vector <BulletObject*> p_bullet_list;

	int x_val;
	int y_val;
	int x;
	int y;

	int frame_bullet;
	int frame_tail;
	int frame_player;
	int frame_die;

	Music sound;

};


#endif // !PLAYER_H_
