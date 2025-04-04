#ifndef MENU_H_
#define MENU_H_

#include "CommonFunc.h"
#include "Player.h"
#include "ThreatsObject.h"
class Menu
{
public:
    Menu();
    ~Menu();

    void LoadMenu_Game(SDL_Renderer* renderer);                   
    void RenderMenu(SDL_Renderer* renderer, int mouseX, int mouseY);

    void HandleMouseEvent(SDL_Event& event, int mouseX, int mouseY, bool mouseClicked);
    void Update(SDL_Renderer* renderer);
    int GetSelectedOption() { return selectedOption; }
    bool IsMouseOver(const SDL_Rect& rect, int mouseX, int mouseY);

    void set_inMenu(bool& in_menu) { inMenu = in_menu; }
    bool get_inMenu() { return inMenu; }

    void set_Quit(bool quit) { Quit = quit; }
    bool get_Quit() { return Quit; }

    // GAME OVER
    void Load_Game_Over(SDL_Renderer* renderer);
    void Render_Game_Over(SDL_Renderer* renderer, int mouseX, int mouseY);
    void HandleMouse_GameOver(SDL_Event& event, int mouseX, int mouseY, bool mouseClicked);
    void Update_GameOver(SDL_Renderer* renderer);

    void set_inGameOver(bool& in_Gameover) { inGameOver = in_Gameover; }
    bool get_inGameOver() { return inGameOver; }
    // END GAME
    void Load_End_Game(SDL_Renderer* renderer);
    void Render_End_Game(SDL_Renderer* renderer);

private:
    // game start
    SDL_Texture* help_texture;
    SDL_Rect rect_help;

    SDL_Texture* back_texture;
    SDL_Rect rect_back;

    vector<SDL_Texture*> buttonTextures;
    vector<SDL_Rect> buttonRects;  

    int selectedOption;           
    int pressedOption;

    bool inMenu;
    bool Quit;
    Uint32 start_time;
    // game over
    bool inGameOver;
    vector<SDL_Texture*> gameOverTextures;
    vector<SDL_Rect> gameOverRects;
    // End Game
    bool inEndGame;
    SDL_Texture* endGame_Texture;
    SDL_Rect endGame_Rect;
};
#endif // !MENU_H_
