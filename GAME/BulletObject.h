
#ifndef BULLET_OBJECT_H_
#define BULLET_OBJECT_H_

#include "CommonFunc.h"

class BulletObject
{
public:
	BulletObject();
	~BulletObject();

	bool loadImg_Bullet(SDL_Renderer* renderer, const char* path, int frame_number);
	void setCLip_Bullet(const int frame_number);
	void Render_Bullet(SDL_Renderer* renderer, SDL_Rect rectquad, int& frame1);
	void setRect_Bullet(const int& x, const int& y);
	int get_bullet_x_pos() const { return rect_bullet.x; }
	int get_bullet_y_pos() const { return rect_bullet.y; }



	void set_x_val(const int& xVal) { x_val = xVal; }
	void set_y_val(const int& yVal) { y_val = yVal; }
	int get_x_val() const { return x_val; }	
	int get_y_val() const { return y_val; }

	void set_is_move(const bool& isMove) { is_move = isMove; }
	bool get_is_move() const { return is_move; }

	void HandleMove(const int& x_border, const int& y_border);

private:
	SDL_Texture* Texture_Bullet;
	SDL_Rect rect_bullet;
	int width_frame;
	int height_frame;
	vector <SDL_Rect> frame_clips_bullet;
	int frame;

	int x_val;
	int y_val;
	bool is_move;
};


#endif // !BULLET_OBJECT_H_
