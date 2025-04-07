
#ifndef COMMON_FUNCTION_H_
#define COMMON_FUNCTION_H_

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <string>
#include <iostream>
#include <windows.h>
#include <vector>
#include <ctime>
using namespace std;

static SDL_Window* window;
static SDL_Renderer* renderer;
static SDL_Event event;

// Kích thước màn hình 
const int SCREEN_WIDTH  = 1200;
const int SCREEN_HEIGHT = 700;

const int BACKGROUND_WIDTH = 2200;
const int BACKGROUND_HEIGTH = 700;

const int NUMBER_DIE = 13;
const int VOLUME_MUSIC = 64;
const int X_SCORE = 40;
const int Y_SCORE = 640;
const int X_BEST_SCORE = 520;
const int Y_BEST_SCORE = 650;

namespace SDLCommonFunc
{
	bool CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2);
}

#endif // !COMMON_FUNCTION_H_

// threats 
//vector <ThreatsObject*> MakeThreatsList(const bool is_line, 
//										const bool is_shape,  
//										int x_start, int y_start, 
//										int kc_x, int kc_y) {
//	vector <ThreatsObject*> list_threats;
//
//	ThreatsObject* threats_lv1 = new ThreatsObject[7];
//	for (int i = 0;i < 7;i++) {
//		ThreatsObject* p_threat = (threats_lv1 + i);
//		if (p_threat != NULL) {
//			bool ret = p_threat->loadImg(renderer, "threats//kamikaze_sheet.png", 4);
//			if (ret) {
//				p_threat->setCLip(4);
//			}
//			if (is_shape) {
//				if (i <= 3) {
//					p_threat->set_x_pos(x_start - i * kc_x);
//					p_threat->set_y_pos(y_start + i * kc_y);
//				}
//				else {
//					p_threat->set_x_pos((x_start - 6 * kc_x) + i * kc_x);
//					p_threat->set_y_pos((x_start - 6 * kc_x) + i * kc_y);
//				}
//			}
//			else if (is_line) {
//				p_threat->set_x_pos(x_start + i * kc_x);
//				p_threat->set_y_pos(y_start + i * kc_y);
//			}
//			list_threats.push_back(p_threat);
//		}
//	}
//
//	ThreatsObject* threats_lv2 = new ThreatsObject[3];
//}