
#include "CommonFunc.h"
#include "MoveBackground.h"
#include "Player.h"
#include "BulletObject.h"
#include "ThreatsObject.h"
#include "Explosion.h"
#include "Menu.h"
#include "Music.h"
#include "Text.h"

Player player;
MoveBackground background;
Explosion explosion1;
Explosion explosion2;
Menu menu;
Music music;
Text text;

bool InitData()
{
	bool success = 1;
	// khởi tạo SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		cout << SDL_GetError();
		success = 0;
	}
	// tạo cửa sổ 
	window = SDL_CreateWindow("GAME 2D", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == NULL) {
		cout << SDL_GetError();
		success = 0;
	}
	// tạo render 
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL) {
		cout << SDL_GetError();
		SDL_Quit();
		success = 0;
	}
	SDL_SetRenderDrawColor(renderer, 60, 60, 60, 225);
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
	// khoi tạo SDL_image
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags)) {
		cout << SDL_GetError();
		SDL_Quit();
		success = 0;
	}
	int flags = MIX_INIT_MP3;
	if (Mix_Init(flags) != flags) {
		cout << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << endl;
		success = 0;
	}
	// khởi tạo SDL_mixer
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
		cout << "SDL_mixer could not open audio! SDL_mixer Error: " << Mix_GetError() << endl;
		success = false;
	}
	Mix_VolumeMusic(VOLUME_MUSIC);
	// khởi tạo SDL_ttf
	if (TTF_Init() == -1) {
		cout << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError();
		success = false;
	}
	return success;
}

void Close()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
	TTF_Quit();
}

void changeBackground(vector<const char*> imagePaths, vector <int> speeds)
{
	vector<SDL_Texture*> textures = background.loadLayerBackground(renderer, imagePaths);
	for (int i = 0;i < textures.size();i++)
	{
		if (textures[i] == NULL) {
			cout << SDL_GetError();
		}
	}
	background.setSpeeds(speeds);
}

bool CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2)
{
	int left_a = object1.x + 5;
	int right_a = object1.x + object1.w - 5;
	int top_a = object1.y + 5;
	int bottom_a = object1.y + object1.h - 5;

	int left_b = object2.x + 5;
	int right_b = object2.x + object2.w - 5;
	int top_b = object2.y + 5;
	int bottom_b = object2.y + object2.h - 5;

	// Case 1: size object 1 < size object 2
	if (left_a > left_b && left_a < right_b)
	{
		if (top_a > top_b && top_a < bottom_b)
		{
			return true;
		}
	}

	if (left_a > left_b && left_a < right_b)
	{
		if (bottom_a > top_b && bottom_a < bottom_b)
		{
			return true;
		}
	}

	if (right_a > left_b && right_a < right_b)
	{
		if (top_a > top_b && top_a < bottom_b)
		{
			return true;
		}
	}

	if (right_a > left_b && right_a < right_b)
	{
		if (bottom_a > top_b && bottom_a < bottom_b)
		{
			return true;
		}
	}

	// Case 2: size object 1 > size object 2
	if (left_b > left_a && left_b < right_a)
	{
		if (top_b > top_a && top_b < bottom_a)
		{
			return true;
		}
	}

	if (left_b > left_a && left_b < right_a)
	{
		if (bottom_b > top_a && bottom_b < bottom_a)
		{
			return true;
		}
	}

	if (right_b > left_a && right_b < right_a)
	{
		if (top_b > top_a && top_b < bottom_a)
		{
			return true;
		}
	}

	if (right_b > left_a && right_b < right_a)
	{
		if (bottom_b > top_a && bottom_b < bottom_a)
		{
			return true;
		}
	}

	// Case 3: size object 1 = size object 2
	if (top_a == top_b && right_a == right_b && bottom_a == bottom_b)
	{
		return true;
	}

	return false;
}

// threats level 1
vector <ThreatsObject*> MakeThreatsList_lv1(int number_of_threats)
{
	vector <ThreatsObject*> list_threats;
	for (int i = 0; i < number_of_threats; i++)
	{
		ThreatsObject* p_threat = new ThreatsObject();
		if (p_threat != NULL)
		{
			if (i <= 1) {
				p_threat->set_x_pos(1220 - i * 45);
				p_threat->set_y_pos(100 + i * 60);
			}
			else {
				p_threat->set_x_pos(1020 + i * 45);
				p_threat->set_y_pos(100 + i * 60);
			}
			
			bool ret = p_threat->LoadImg_Threats("threats//kamikaze_sheet.png", renderer, 4);
			if (ret)
			{
				p_threat->set_clips_threats(4);
				list_threats.push_back(p_threat);
			}
		}
	}
	return list_threats;
}
void ShowThreats_lv1(vector <ThreatsObject*> list_threats) {
	for (int i = 0; i < list_threats.size(); i++) {
		ThreatsObject* p_threat = list_threats[i];
		if (p_threat != NULL) {
			// Tính vector hướng từ threats đến máy bay
			float dx = player.get_x() - p_threat->get_x_pos() + 30;
			float dy = player.get_y() - p_threat->get_y_pos() + 5;
			// Tính độ dài vector
			float length = sqrt(dx * dx + dy * dy);

			if (length > 0) {
				float x_val = (dx / length) * 17; 
				float y_val = (dy / length) * 10; 

				if (dx != 0 && dy != 0) {
					p_threat->set_x_val(x_val);
					p_threat->set_y_val(y_val);
					p_threat->set_x_pos(p_threat->get_x_pos() + p_threat->get_x_val());
					p_threat->set_y_pos(p_threat->get_y_pos() + p_threat->get_y_val());
				}
			}
			p_threat->Show_threats(renderer, 4);
		}
	}
}

// threats level 2
vector <ThreatsObject*> MakeThreatsList_lv2(const int number_of_threats, const int y_start, const int kc_x, const int kc_y)
{
	vector <ThreatsObject*> list_threats;
	for (int i = 0; i < number_of_threats; i++)
	{
		ThreatsObject* p_threat = new ThreatsObject();
		if (p_threat != NULL)
		{
			p_threat->set_x_pos(1220 + i * kc_x);
			p_threat->set_y_pos(y_start + i * kc_y);

			bool ret = p_threat->LoadImg_Threats("threats//enemy-z.png", renderer, 1);
			if (ret)
			{
				p_threat->set_clips_threats(1);
				list_threats.push_back(p_threat);
			}
		}
	}
	return list_threats;
}
void ShowThreats_lv2(vector <ThreatsObject*> list_threats) {

	for (int i = 0; i < list_threats.size(); i++) {
		ThreatsObject* p_threat = list_threats[i];
		if (p_threat != NULL) {
			float x_val = -9;
			float y_val = 0;
			p_threat->set_x_val(x_val);
			p_threat->set_y_val(y_val);
			p_threat->set_x_pos(p_threat->get_x_pos() + p_threat->get_x_val());
			p_threat->set_y_pos(p_threat->get_y_pos() + p_threat->get_y_val());
			p_threat->Show_threats(renderer, 1);
		}
	}
}

// threats level 3
vector <ThreatsObject*> MakeThreatsList_lv3(int number_of_threats, int x_start, int y_start, int kc_x, int kc_y) {
	vector <ThreatsObject*> list_threats;
	for (int i = 0; i < number_of_threats; i++) {
		ThreatsObject* p_threat = new ThreatsObject();
		if (p_threat != NULL) {
			bool ret = p_threat->LoadImg_Threats("threats//enemy_circle.png", renderer, 4);
			if (ret) {
				p_threat->set_clips_threats(4);
			}
			else if (!ret) {
				cout << "load img threat 3 is " << SDL_GetError();
			}
			p_threat->set_x_pos(x_start + i * kc_x);
			p_threat->set_y_pos(y_start + i * kc_y);
			list_threats.push_back(p_threat);
		}
	}
	return list_threats;
}
void ShowThreats_lv3(vector <ThreatsObject*> list_threats,int number_of_threats, float x_val, float y_val) {
	for (int i = 0; i < list_threats.size(); i++) {
		ThreatsObject* p_threat = list_threats.at(i);
		if (p_threat != NULL) {
			// Thiết lập vận tốc
			p_threat->set_x_val(x_val);
			p_threat->set_y_val(y_val);
			p_threat->set_x_pos(p_threat->get_x_pos() + p_threat->get_x_val());
			p_threat->set_y_pos(p_threat->get_y_pos() + p_threat->get_y_val());

			// Hiển thị threats
			if (p_threat->get_x_pos() < 1190) {
				p_threat->ShowBullet(renderer, 5, 30, -12, 2);
			}
			p_threat->Show_threats(renderer, 4);
		}
	}
}

// thretas level 4
vector <ThreatsObject*> MakeThreatsList_lv4(int number_of_threats, int x_start, int y_start, int kc_x, int kc_y) {
	vector <ThreatsObject*> list_threats;
	for (int i = 0; i < number_of_threats; i++) {
		ThreatsObject* p_threat = new ThreatsObject();
		if (p_threat != NULL) {
			bool ret = p_threat->LoadImg_Threats("threats//enemy_zig_zag.png", renderer, 4);
			if (ret) {
				p_threat->set_clips_threats(4);
			}
			else if (!ret) {
				cout << "load img threat 4 is " << SDL_GetError();
			}
			p_threat->set_x_pos(x_start + i * kc_x);
			p_threat->set_y_pos(y_start + i * kc_y);
			list_threats.push_back(p_threat);
		}
	}
	return list_threats;
}
void ShowThreats_lv4(vector <ThreatsObject*> list_threats, int number_of_threats, float x_val, float y_val) {
	for (int i = 0; i < list_threats.size(); i++) {
		ThreatsObject* p_threat = list_threats.at(i);
		if (p_threat != NULL) {
			// Thiết lập vận tốc
			p_threat->set_x_val(x_val);
			p_threat->set_y_val(y_val);
			p_threat->set_x_pos(p_threat->get_x_pos() + p_threat->get_x_val());
			p_threat->set_y_pos(p_threat->get_y_pos() + p_threat->get_y_val());

			// Hiển thị threats
			if (p_threat->get_x_pos() < 1190) {
				p_threat->ShowBullet(renderer, 5, 40, -15, 4);
			}
			p_threat->Show_threats(renderer, 4);
		}
	}
}

vector<vector<ThreatsObject*>> Make_Threats_list(vector<pair<int, int>>& Time_delay) {
	vector<vector<ThreatsObject*>> Threats_list;
	for (int i = 0; i < 29; i++) {
		Threats_list.push_back(MakeThreatsList_lv1(5));
		Time_delay.push_back( {3000 + i * 4000, 1} );
	}

	for (int i = 0; i < 29; i++) {
		if (i % 2 == 0) {
			Threats_list.push_back(MakeThreatsList_lv2(5, 150, 100, 0));
		}
		else {
			Threats_list.push_back(MakeThreatsList_lv2(5, 150, 0, 100));
		}
		Time_delay.push_back( {5000 + i * 4000, 2} );
	}

	for (int i = 0;i < 20; i++) {
		Threats_list.push_back(MakeThreatsList_lv3(2, 1220, 100, 100, 300));
		Time_delay.push_back( { 8000 + i * 6000, 3 } );
	}

	for (int i = 0; i < 21;i++) {
		Threats_list.push_back(MakeThreatsList_lv4(1, 1220, 350, 0, 0));
		Time_delay.push_back({ 6000 + i * 6000, 4 });
	}

	return Threats_list;
}
void Render_Threats_list(vector<vector<ThreatsObject*>>& Threats_list, Uint32 current_time, Uint32 start_time, vector <pair<int,int>> Time_delay) {
	for (int i = 0; i < Threats_list.size(); i++) {
		if (current_time - start_time >= Time_delay[i].first) {
			switch (Time_delay[i].second) {
			case 1:
				ShowThreats_lv1(Threats_list[i]);
				break;
			case 2:
				ShowThreats_lv2(Threats_list[i]);
				break;
			case 3:
				ShowThreats_lv3(Threats_list[i], Threats_list[i].size(), -7, 0);
				break;
			case 4:
				ShowThreats_lv4(Threats_list[i], Threats_list[i].size(), -5, 0);
				break;
			}
		}
	}
}

void ResetGame(vector<vector<ThreatsObject*>>& Threats_list, vector<pair<int, int>>& Time_delay) {
	// Giải phóng bộ nhớ threats cũ
	for (auto& threat_group : Threats_list) {
		for (auto* threat : threat_group) {
			if (threat != nullptr) {
				threat->Free_Threat();
				delete threat;
			}
		}
		threat_group.clear();
	}
	Threats_list.clear();
	Time_delay.clear();

	// Tạo lại threats mới
	Threats_list = Make_Threats_list(Time_delay);
	for (int i = 0; i < Time_delay.size() - 1; i++) {
		for (int j = i + 1; j < Time_delay.size(); j++) {
			if (Time_delay[j].first < Time_delay[i].first) {
				swap(Time_delay[i], Time_delay[j]);
				swap(Threats_list[i], Threats_list[j]);
			}
		}
	}
}

int main(int argc, char* argv[]) {
	if (!InitData()) return -1;
// background 1
	vector<const char*> imagePaths1 = { "background//ruralparallaxsky.png",
										"background//ruralparalaxmoon.png",
										"background//ruralparallaxclouds.png",
										"background//ruralparallaxmountainback2.png",
										"background//ruralparallaxmountainback.png",
										"background//ruralparallaxmountain.png",
										"background//ruralparallaxriver.png",
										"background//ruralparallaxriverfront.png",
										"background//ruralparallaxriverskyredlex.png",
										"background//ruralparallaxvillage.png", };
	vector<SDL_Texture*> textures1 = background.loadLayerBackground(renderer, imagePaths1);
	for (int i = 0;i < textures1.size();i++)
	{
		if (textures1[i] == NULL) {
			cout << SDL_GetError();
			return -1;
		}
	}
	vector <int> speeds1 = { 0, 0, 1, 1, 1, 2, 35, 35, 1, 4 };
	background.setSpeeds(speeds1);
// background 2
	vector<const char*> imagePaths2 = { "citynight//parallaxcitywater.png",
										"citynight//parallaxcitysky.png",
										"citynight//parallaxcitybackgroundmountain.png",
										"citynight//parallaxcitybackgroundmountain2.png",
										"citynight//parallaxcitybuildings.png",
										"citynight//parallaxcitywaterreflexion.png",
										"citynight//parallaxcityfront.png" };
	vector <int> speeds2 = { 0, 1, 2, 2, 3, 3, 35 };
// máy bay
	player.LoadImg_Player(renderer);
	player.Set_Clips_Player();
	player.LoadImg_Tail(renderer, "player//02.png", 2);
	player.Set_Clips(2);
	player.LoadImg_Die(renderer);
	player.Set_Clips_Die();
// threats	
	vector <pair<int,int>> Time_delay;
	vector<vector<ThreatsObject*>> Threats_list = Make_Threats_list(Time_delay);
	for (int i = 0;i < Time_delay.size() - 1;i++) {
		for (int j = i + 1;j < Time_delay.size();j++) {
			if (Time_delay[j].first < Time_delay[i].first) {
				swap(Time_delay[i], Time_delay[j]);
				swap(Threats_list[i], Threats_list[j]);
			}
		}
	}
// explosion 
	bool ret = explosion1.LoadImg_Explosion(renderer, "threats//explosion.png");
	if (!ret) {
		cout << "load img explosion is " << SDL_GetError();
	}
	explosion1.Set_CLips_Expolsion();

	bool ret1 = explosion2.LoadImg_Explosion(renderer, "threats//explosion.png");
	if (!ret1) {
		cout << "load img explosion is " << SDL_GetError();
	}
	explosion2.Set_CLips_Expolsion();
// load music explosion
	music.loadImgVolume(renderer);
	music.setClipsVolume();
	Mix_Chunk* sound_explosion = music.loadSound("music//explosion.mp3");
	Mix_VolumeChunk(sound_explosion, music.getVolume());

	Mix_Chunk* sound_bullet = music.loadSound("music//laser_bullet.mp3");
	Mix_VolumeChunk(sound_bullet, music.getVolume());

	Mix_Music* sound_background = music.loadMusic("music//sound_background.mp3");
	Mix_VolumeMusic(music.getVolume());
// load text
	int score = 0;
	TTF_Font* font = text.loadFont("text//Purisa-BoldOblique.ttf", 20);
	SDL_Color color = { 255, 255, 0, 0 };
	string scoreStr = "SCORE: " + to_string(score);
	SDL_Texture* scoreText = text.loadText(renderer, scoreStr.c_str(), font, color);
	
	int best_score = 0;
	string best_scoreStr = "HIGH SCORE: " + to_string(best_score);
	SDL_Texture* best_scoreText = text.loadText(renderer, best_scoreStr.c_str(), font, color);
// load menu
	menu.LoadMenu_Game(renderer);
	menu.Load_Game_Over(renderer);
	menu.Load_End_Game(renderer);

	int num_die = 0;
	bool inMenu = 1;
	bool inGameOver = 0;
	bool inEnd_Game = 0;
	Uint32 start_time = 0;

	bool quit = 0;
	menu.set_inMenu(inMenu);
	menu.set_Quit(quit);
	menu.set_inGameOver(inGameOver);
	
	while (!quit) {
		int mouseX, mouseY;
		SDL_GetMouseState(&mouseX, &mouseY);
		while (SDL_PollEvent(&event) != 0) {
			if (inMenu) {
				if (event.type == SDL_QUIT) {
					quit = 1;
				}
				else if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
					menu.HandleMouseEvent(event, mouseX, mouseY, true);
					
					inMenu = menu.get_inMenu();
					quit = menu.get_Quit();
				}
			}
			else if (!inMenu && !inGameOver) {
				if (event.type == SDL_QUIT) {
					quit = 1;
				}
				else {
					if (event.type == SDL_KEYDOWN)
					{
						switch (event.key.keysym.sym) {
						case SDLK_1:
							changeBackground(imagePaths1, speeds1);
							break;
						case SDLK_2:
							changeBackground(imagePaths2, speeds2);
							break;
						default:
							break;
						}
					}
					player.HandleInputAction(event, renderer, sound_bullet);
				}
				if (event.type == SDL_MOUSEBUTTONDOWN) {
					if (event.button.button == SDL_BUTTON_LEFT) {
						music.updateVolume(true, mouseX, mouseY);
					}
				}
			}
			else if (inGameOver) {
				if (event.type == SDL_QUIT) {
					quit = 1;
				}
				else if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
					menu.HandleMouse_GameOver(event, mouseX, mouseY, true);
					int selected_option = menu.GetSelectedOption();
					if (selected_option == 3) {
						ResetGame(Threats_list, Time_delay);
						num_die = 0;
						score = 0;
					}
					inGameOver = menu.get_inGameOver();
					quit = menu.get_Quit();
				}
			}
		}
		SDL_RenderClear(renderer);
		if (inMenu) {
			background.update();
			background.RenderBackground(renderer);
			text.renderText(renderer, scoreText, X_SCORE, Y_SCORE);
			text.renderText(renderer, best_scoreText, X_BEST_SCORE, Y_BEST_SCORE);
			player.RenderPlayer(renderer);
			menu.RenderMenu(renderer, mouseX, mouseY);
			// cập nhật trạng thái menu
			menu.Update(renderer);
			inMenu = menu.get_inMenu();
			start_time = SDL_GetTicks();
		}
		else if (!inMenu && !inGameOver) {
			player.HandleContinuousShooting(renderer, sound_bullet);
		// cập nhật vị trí máy bay
			player.UpdatePlayer();
		// background
			background.update();
			background.RenderBackground(renderer);
		// text
			text.renderText(renderer, scoreText, X_SCORE, Y_SCORE);
			scoreStr = "SCORE: " + to_string(score);
			scoreText = text.loadText(renderer, scoreStr.c_str(), font, color);
			text.renderText(renderer, best_scoreText, X_BEST_SCORE, Y_BEST_SCORE);
		// music
			music.renderVolume(renderer);
			music.play(sound_background);
			Mix_VolumeMusic(music.getVolume());
			Mix_VolumeChunk(sound_explosion, music.getVolume());
			Mix_VolumeChunk(sound_bullet, music.getVolume());
		// máy bay
			player.RenderPlayer(renderer);
		// show threats
			Uint32 current_time = SDL_GetTicks();
			Render_Threats_list(Threats_list, current_time, start_time, Time_delay);
		//check collision bullet_player vs threats
			vector <BulletObject*> bullet_list = player.get_bullet_list();
			for (int i = 0; i < bullet_list.size(); ++i)
			{
				BulletObject* p_bullet = bullet_list[i];
				if (p_bullet != NULL)
				{
					for (size_t a = 0; a < Threats_list.size(); a++) {
						for (size_t b = 0; b < Threats_list[a].size(); b++) {
							ThreatsObject* p_threat = Threats_list[a][b];
							if (p_threat != NULL)
							{
								SDL_Rect brect;
								brect.x = p_bullet->get_bullet_x_pos();
								brect.y = p_bullet->get_bullet_y_pos();
								brect.w = 40;
								brect.h = 20;
								//
								SDL_Rect trect;
								trect.x = p_threat->get_x_pos();
								trect.y = p_threat->get_y_pos();
								trect.w = p_threat->get_width_frame();
								trect.h = p_threat->get_height_frame();
								//
								bool bCol = CheckCollision(brect, trect);
								if (bCol && trect.x <= 1100)
								{
									int explosion_x = p_threat->get_x_pos() - 60;
									int explosion_y = p_threat->get_y_pos() - 60;
									explosion1.set_is_explosion(1, explosion_x, explosion_y);
									player.EraseBullet(i);
									music.play(sound_explosion);
									p_threat->Free_Threat();
									Threats_list[a].erase(Threats_list[a].begin() + b);
									score += 10;
								}
							}
						}
					}
				}
			}
			explosion1.Show_Explosion(renderer);

		// check collision player vs threats
			for (size_t a = 0; a < Threats_list.size(); a++) 
			{
				for (size_t b = 0; b < Threats_list[a].size(); b++)
				{
					ThreatsObject* p_threat = Threats_list[a][b];
					SDL_Rect rect_player;
					rect_player.x = player.get_x();
					rect_player.y = player.get_y();
					rect_player.w = 160;
					rect_player.h = 60;
					//
					SDL_Rect rect_threat;
					rect_threat.x = p_threat->get_x_pos();
					rect_threat.y = p_threat->get_y_pos();
					rect_threat.w = p_threat->get_width_frame();
					rect_threat.h = p_threat->get_height_frame();
					//
					bool check1 = CheckCollision(rect_player, rect_threat);
					if (check1) {
						num_die++;
						int explosion_x = p_threat->get_x_pos() - 60;
						int explosion_y = p_threat->get_y_pos() - 60;
						explosion2.set_is_explosion(1, explosion_x, explosion_y);
						music.play(sound_explosion);
						p_threat->Free_Threat();
						Threats_list[a].erase(Threats_list[a].begin() + b);
					}
				}
			}
			
		//check collision player vs bullet threats
			for (int i = 0;i < Threats_list.size();i++)
			{
				for (int j = 0;j < Threats_list[i].size();j++)
				{
					if (Time_delay[i].second == 3 || Time_delay[i].second == 4 ) {
						ThreatsObject* p_threat = Threats_list[i][j];
						SDL_Rect rect_player;
						rect_player.x = player.get_x();
						rect_player.y = player.get_y();
						rect_player.w = 160;
						rect_player.h = 60;
						vector <BulletObject*> t_list_bullet = p_threat->get_bullet_threats();
						for (int b = 0; b < t_list_bullet.size(); b++) {
							BulletObject* t_bullet = t_list_bullet.at(b);
							SDL_Rect t_rect_bullet;
							t_rect_bullet.x = t_bullet->get_bullet_x_pos();
							t_rect_bullet.y = t_bullet->get_bullet_y_pos();
							t_rect_bullet.w = 20;
							t_rect_bullet.h = 15;
							bool check1 = CheckCollision(rect_player, t_rect_bullet);
							if (check1) {
								num_die++;
								p_threat->EraseBullet(b);
							}
						}
					}
				}
			}
			explosion2.Show_Explosion(renderer);

			for (size_t a = 0; a < Threats_list.size(); a++)
			{
				for (size_t b = 0; b < Threats_list[a].size(); b++)
				{
					ThreatsObject* p_threat = Threats_list[a][b];
					SDL_Rect rect_threat;
					rect_threat.x = p_threat->get_x_pos();
					rect_threat.y = p_threat->get_y_pos();
					rect_threat.w = p_threat->get_width_frame();
					rect_threat.h = p_threat->get_height_frame();
					if (rect_threat.x < 10) {
						p_threat->Free_Threat();
						Threats_list[a].erase(Threats_list[a].begin() + b);
					}
				}
			}

			player.Set_Frame_Die(num_die);
			if (num_die >= NUMBER_DIE) {
				player.Set_Rect_Player(20, 100);
				player.Set_x_val(0);
				player.Set_y_val(0);
				player.Set_frame_player(3);
				explosion1.set_is_explosion(false, 0, 0);
				explosion2.set_is_explosion(false, 0, 0);
				player.LoadImg_Tail(renderer, "player//02.png", 2);
				player.Set_Clips(2);
				inGameOver = 1;
				menu.set_inGameOver(inGameOver);
			}
			int n = Threats_list.size();
			int m = Threats_list[n-1].size();
			if (m == 0) {
				inGameOver = 1;
				menu.set_inGameOver(inGameOver);
			}
		}
		else {
			if (score > best_score) {
				best_score = score;
				best_scoreStr = "HIGH SCORE: " + to_string(best_score);
				best_scoreText = text.loadText(renderer, best_scoreStr.c_str(), font, color);
			}
			background.update();
			background.RenderBackground(renderer);
			Mix_VolumeMusic(0);
			Mix_VolumeChunk(sound_explosion, 0);
			Mix_VolumeChunk(sound_bullet, 0);
			text.renderText(renderer, scoreText, X_SCORE, Y_SCORE);
			text.renderText(renderer, best_scoreText, X_BEST_SCORE, Y_BEST_SCORE);
			player.RenderPlayer(renderer);
			if (num_die < NUMBER_DIE) {
				menu.Render_End_Game(renderer);
			}
			menu.Render_Game_Over(renderer, mouseX, mouseY);
			// cập nhật trạng thái menu
			menu.Update_GameOver(renderer);
			inGameOver = menu.get_inGameOver();
			start_time = SDL_GetTicks();
		}
			SDL_RenderPresent(renderer);
			SDL_Delay(30);
	}
	Close();
	SDL_DestroyTexture(scoreText);
	TTF_CloseFont(font);
	scoreText = NULL;
	SDL_DestroyTexture(best_scoreText);
	best_scoreText = NULL;
	return -1;
}