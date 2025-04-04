
#ifndef EXPLOSION_H_
#define EXPLOSION_H_

#include "CommonFunc.h"

class Explosion
{
public:
	Explosion();
	~Explosion();
	bool LoadImg_Explosion(SDL_Renderer* renderer, const char* path);
	void Set_CLips_Expolsion();
	void Show_Explosion(SDL_Renderer* renderer);

	void set_is_explosion(bool isExplosion , int expX, int expY) 
	{
		is_explosion = isExplosion; exp_x = expX; exp_y = expY;
	}
	bool get_is_explosion() { return is_explosion; }
	

private:
	int frame;
	vector <SDL_Rect> frame_clips;
	int width_frame;
	int height_frame;
	SDL_Texture* texture;
	Uint32 last_time;
	bool is_explosion;
	int exp_x;
	int exp_y;
};
#endif // !EXPLOSION_H_
