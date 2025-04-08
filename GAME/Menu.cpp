
#include "Menu.h"

Menu::Menu() {
    help_texture = NULL;
    rect_help = { 0, 0, 0, 0 };

    back_texture = NULL;
    rect_back = { 0, 0, 0, 0 };

    start_time = SDL_GetTicks();

    selectedOption = -1;
    pressedOption = -1;
    
    inMenu = true;
    Quit = false;
    inGameOver = false;
    inEndGame = false;
    endGame_Texture = NULL;
    endGame_Rect = { 0, 0, 0, 0 };
}

Menu::~Menu() {
    if (help_texture) {
        SDL_DestroyTexture(help_texture);
    }
    for (auto texture : buttonTextures) {
        SDL_DestroyTexture(texture);
    }
}

void Menu::LoadMenu_Game(SDL_Renderer* renderer) {
    // hình ảnh khi bấm help
    SDL_Texture* new_texture = NULL;
    SDL_Surface* load_surface = IMG_Load("menu//help.png");
    if (load_surface == NULL) {
        cout << "load img help" << IMG_GetError();
    }
    else {
        new_texture = SDL_CreateTextureFromSurface(renderer, load_surface);
        if (new_texture != NULL)
        {
            rect_help.w = load_surface->w;
            rect_help.h = load_surface->h;
        }
        SDL_FreeSurface(load_surface);
    }
    help_texture = new_texture;

    // LOAD HÌNH ẢNH BACK
    SDL_Texture* texture = NULL;
    SDL_Surface* surface = IMG_Load("menu//back.png");
    if (surface == NULL) {
        cout << "load img help" << IMG_GetError();
    }
    else {
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        if (texture != NULL)
        {
            rect_back.w = surface->w;
            rect_back.h = surface->h;
        }
        SDL_FreeSurface(surface);
    }
    back_texture = texture;
    

    // Tải hình ảnh các nút
    vector<const char*> buttonPaths = {
        "menu//menu_start.png",
        "menu//menu_exit.png",
        "menu//menu_help.png"
    };

    for (const char* path : buttonPaths) {
        SDL_Surface* buttonSurface = IMG_Load(path);
        if (!buttonSurface) {
            cout << "Failed to load button image: " << IMG_GetError() << endl;
            continue;
        }
        SDL_Texture* buttonTexture = SDL_CreateTextureFromSurface(renderer, buttonSurface);
        SDL_FreeSurface(buttonSurface);

        if (!buttonTexture) {
            cout << "Failed to create button texture: " << SDL_GetError() << endl;
            continue;
        }
        buttonTextures.push_back(buttonTexture);
    }

    // Thiết lập vị trí và kích thước các nút
    buttonRects.push_back({ 550, 200, 100, 50 }); // Start button
    buttonRects.push_back({ 550, 280, 100, 50 }); // Exit button
    buttonRects.push_back({ 550, 360, 100, 50 }); // Help button
}

void Menu::RenderMenu(SDL_Renderer* renderer, int mouseX, int mouseY) {
    // Hiển thị các nút
    for (size_t i = 0; i < buttonTextures.size(); i++) {
        // Nếu có nút được nhấn, làm mờ các nút khác
        if (pressedOption != -1 && i != pressedOption) {
            SDL_SetTextureAlphaMod(buttonTextures[i], 100); // Làm mờ
        }
        else {
            SDL_SetTextureAlphaMod(buttonTextures[i], 255); // Hiển thị bình thường
        }

        // Đổi màu nút khi con trỏ chuột trỏ vào hoặc nút được nhấn
        if (i == selectedOption || IsMouseOver(buttonRects[i], mouseX, mouseY) || i == pressedOption) {
            SDL_SetTextureColorMod(buttonTextures[i], 255, 0, 0); // Màu đỏ
        }
        else {
            SDL_SetTextureColorMod(buttonTextures[i], 255, 255, 255); // Màu trắng
        }
        // Render nút
        SDL_RenderCopy(renderer, buttonTextures[i], NULL, &buttonRects[i]);
    }

    // nếu đang ở nút help
    if (pressedOption == 2) {
        rect_help = { 200, 100, 800, 500 };
        SDL_RenderCopy(renderer, help_texture, NULL, &rect_help);

        rect_back = { 750, 495, 120, 60 };
        // Đổi màu nút Back khi trỏ vào
        if (IsMouseOver(rect_back, mouseX, mouseY)) {
            SDL_SetTextureColorMod(back_texture, 255, 0, 0); // Màu đỏ
        }
        else {
            SDL_SetTextureColorMod(back_texture, 255, 255, 255); // Màu trắng
        }
        SDL_RenderCopy(renderer, back_texture, NULL, &rect_back);
    }
}

void Menu::HandleMouseEvent(SDL_Event& event, int mouseX, int mouseY, bool mouseClicked) {
    if (pressedOption != -1) {
        //
        if (pressedOption == 2 && IsMouseOver(rect_back, mouseX, mouseY)) {
            if (mouseClicked) {
                pressedOption = -1; // Reset trạng thái nhấn nút
                selectedOption = -1; // Reset nút được chọn
            }
        }
        return;
    }
    selectedOption = -1; // Mặc định không có nút nào được chọn
    for (size_t i = 0; i < buttonRects.size(); i++) {
        if (IsMouseOver(buttonRects[i], mouseX, mouseY)) {
            selectedOption = i; // Đánh dấu nút được trỏ vào

            if (mouseClicked) {
                pressedOption = i; // lưu lại nút được nhấn
                if (i == 0) { // Nếu bấm vào Start
                    start_time = SDL_GetTicks(); // Lưu thời điểm nhấn Start
                }
                else if (i == 1) { // Nếu bấm vào Exit
                    SDL_Delay(1000);
                    Quit = 1; // Đặt cờ thoát game
                }
                else if (i == 2) { // Nếu bấm vào Help
                    
                }
            }
        }
    }
}

void Menu::Update(SDL_Renderer* renderer) {
    if (pressedOption == 0) {
        Uint32 current_time = SDL_GetTicks(); // Lấy thời gian hiện tại
        if (current_time - start_time >= 2000) { // Kiểm tra nếu đã đủ 2 giây
            inMenu = 0;
            inGameOver = 0;// Thoát menu và vào game
            pressedOption = -1;
            selectedOption = -1;
        }
    }
}

bool Menu::IsMouseOver(const SDL_Rect& rect, int mouseX, int mouseY) {
    return mouseX >= rect.x && mouseX <= rect.x + rect.w &&
        mouseY >= rect.y && mouseY <= rect.y + rect.h;
}

// game_over

void Menu::Load_Game_Over(SDL_Renderer* renderer) {
    vector<const char*> gameoverPaths = {
        "menu//gameover_retry.png",
        "menu//gameover_exit.png",
    };

    for (const char* path : gameoverPaths) {
        SDL_Surface* gameoverSurface = IMG_Load(path);
        if (!gameoverSurface) {
            cout << "Failed to load button image: " << IMG_GetError() << endl;
            continue;
        }
        SDL_Texture* gameoverTexture = SDL_CreateTextureFromSurface(renderer, gameoverSurface);
        SDL_FreeSurface(gameoverSurface);

        if (!gameoverTexture) {
            cout << "Failed to create button texture: " << SDL_GetError() << endl;
            continue;
        }
        gameOverTextures.push_back(gameoverTexture);
    }

    // Thiết lập vị trí và kích thước các nút
    gameOverRects.push_back({ 550, 300, 100, 50 }); // Retry button
    gameOverRects.push_back({ 550, 380, 100, 50 }); // Exit button
}

void Menu::Render_Game_Over(SDL_Renderer* renderer, int mouseX, int mouseY) {
    for (size_t i = 0; i < gameOverTextures.size(); i++) {
        // Nếu có nút được nhấn, làm mờ các nút khác
        if (pressedOption != -1 && i != pressedOption) {
            SDL_SetTextureAlphaMod(gameOverTextures[i], 100); // Làm mờ
        }
        else {
            SDL_SetTextureAlphaMod(gameOverTextures[i], 255); // Hiển thị bình thường
        }

        // Đổi màu nút khi con trỏ chuột trỏ vào hoặc nút được nhấn
        if (i == selectedOption || IsMouseOver(gameOverRects[i], mouseX, mouseY) || i == pressedOption) {
            SDL_SetTextureColorMod(gameOverTextures[i], 255, 0, 0); // Màu đỏ
        }
        else {
            SDL_SetTextureColorMod(gameOverTextures[i], 255, 255, 255); // Màu trắng
        }
        // Render nút
        SDL_RenderCopy(renderer, gameOverTextures[i], NULL, &gameOverRects[i]);
    }
}

void Menu::HandleMouse_GameOver(SDL_Event& event, int mouseX, int mouseY, bool mouseClicked) {
    if (pressedOption != -1) {
        return;
    }
    selectedOption = -1; // Mặc định không có nút nào được chọn
    for (size_t i = 0; i < gameOverRects.size(); i++) {
        if (IsMouseOver(gameOverRects[i], mouseX, mouseY)) {
            if (i == 0) { selectedOption = 3; } // đánh dấu nếu bấm nút retry
            if (i == 1) { selectedOption = 4; } // đánh dấu nếu nhấn nút exit 

            if (mouseClicked) {
                pressedOption = i + 3; // lưu lại nút được nhấn
                if (i == 0) { // Nếu bấm vào Retry
                    start_time = SDL_GetTicks(); // Lưu thời điểm nhấn Retry
                }
                else if (i == 1) { // Nếu bấm vào Exit
                    SDL_Delay(1000);
                    Quit = 1; // Đặt cờ thoát game
                }
            }
        }
    }
}

void Menu::Update_GameOver(SDL_Renderer* renderer) {
    if (pressedOption == 3) {
        Uint32 current_time = SDL_GetTicks(); // Lấy thời gian hiện tại
        if (current_time - start_time >= 2000) { // Kiểm tra nếu đã đủ 2 giây
            inGameOver = 0; // Thoát màn hình game over và vào lại game
            inMenu = 0;
            pressedOption = -1;
            selectedOption = -1;
        }
    }
}

// END GAME

void Menu::Load_End_Game(SDL_Renderer* renderer) {
    SDL_Texture* new_Texture = NULL;
    SDL_Surface* endGameSurface = IMG_Load("menu//menu_endgame.png");
    if (endGameSurface == NULL) {
        cout << "Load surface end game" << IMG_GetError() << endl;
    }
    else {
        new_Texture = SDL_CreateTextureFromSurface(renderer, endGameSurface);
        SDL_FreeSurface(endGameSurface);
    }
    if (new_Texture == NULL) {
        cout << "Create texture end game" << SDL_GetError() << endl;
    }
    else {
        endGame_Texture = new_Texture;
    }
}

void Menu::Render_End_Game(SDL_Renderer* renderer) {
    endGame_Rect = { 0, 0, 1200, 700 };
    SDL_RenderCopy(renderer, endGame_Texture, NULL, &endGame_Rect);
}

