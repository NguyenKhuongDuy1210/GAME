
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

#endif // !COMMON_FUNCTION_H_