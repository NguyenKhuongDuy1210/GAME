
#ifndef THREATS_OBJECT_H_
#define THREATS_OBJECT_H_

#include "CommonFunc.h"
#include "BulletObject.h"

class ThreatsObject
{
public:
	ThreatsObject();
	~ThreatsObject();

	void set_x_val(const float& xVal) { x_val = xVal; }
	void set_y_val(const float& yVal) { y_val = yVal; }
	float get_x_val() const { return x_val; }
	float get_y_val() const { return y_val; }
	
	void set_x_pos(const float& xPos) { x_pos = xPos; }
	void set_y_pos(const float& yPos) { y_pos = yPos; }
	float get_x_pos() const { return x_pos; }
	float get_y_pos() const { return y_pos; }
	
	void set_clips_threats(int frame_number);
	bool LoadImg_Threats(const char* path, SDL_Renderer* renderer, int frame_number);
	void Show_threats(SDL_Renderer* renderer,int frame_number);
	int get_width_frame() { return width_frame; }
	int get_height_frame() { return height_frame; }
// bullet_threats
	void set_bullet_threats(vector <BulletObject*> bullet_list) { t_bullet_list = bullet_list; }
	vector <BulletObject*> get_bullet_threats() { return t_bullet_list; }

	/*void Init_Bullet(SDL_Renderer* renderer, int num_bullets, const int& xVal, const int& yVal);*/
	void Init_Bullet(SDL_Renderer* renderer, const int& x_, const int& y_, const int& xVal, const int& yVal);
	void make_Bullet_Threats(SDL_Renderer* renderer, const int& x_limit, const int& y_limit);
	void EraseBullet(const int idx);
	void ShowBullet(SDL_Renderer* renderer, const int& x_, const int& y_, const int& xVal, const int& yVal);
	bool is_active() const;  // Kiểm tra threat còn hoạt động
	void set_active(bool active);  // Đặt trạng thái active


	void Free_Threat();
private:
	SDL_Rect rect_threat;
	SDL_Texture* texture_threat;
	int frame;
	int width_frame;
	int height_frame;
	SDL_Rect frame_clips[8];
	float x_val;
	float y_val;
	float x_pos;
	float y_pos;
	vector <BulletObject*> t_bullet_list;
	Uint32 last_shot_time;
	Uint32 shot_delay;
	int bullets_in_shot;
	int current_bullets;


	bool m_is_active;
};
#endif // !THREATS_OBJECT_H_