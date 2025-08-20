#ifndef UIMANAGER_HH
#define UIMANAGER_HH

#include <raylib.h>
#include <raymath.h>

using namespace std;

class UIManager {
public:
    UIManager();

    void Render(const int screenWidth, const int screenHeight, const float deltaTime);

protected:

private:
    void Render_MainMenu(const int screenWidth, const int screenHeight, const float deltaTime);
    void Render_Playing(const int screenWidth, const int screenHeight, const float deltaTime);
    void Render_PlayerDead(const int screenWidth, const int screenHeight, const float deltaTime);

    const Texture coinTexture = LoadTexture("Assets/Textures/Coin_001.png");
    Rectangle coinSourceRec = { 0.0f, 0.0f, (float)coinTexture.width, (float)coinTexture.height };
};

#endif