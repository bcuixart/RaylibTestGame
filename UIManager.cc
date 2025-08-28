#include "UIManager.hh"
#include "GameManager.hh"

UIManager::UIManager()
{

}

void UIManager::Render_MainMenu(const int screenWidth, const int screenHeight, const float deltaTime)
{

}

void UIManager::Render_Playing(const int screenWidth, const int screenHeight, const float deltaTime)
{
	DrawTexturePro(coinTexture, coinSourceRec, { (float)screenWidth - 55.f, 5.f, 20.f, 20.f }, {0,0}, 0, GameManager::instance->colorManager->GetCoinColor());

    char buff[100];
    sprintf(buff, "%d", GameManager::instance->GetCoinsTotalUI());
    DrawText(buff, screenWidth - 30, 5, 25, WHITE);
}

void UIManager::Render_PlayerDead(const int screenWidth, const int screenHeight, const float deltaTime)
{
    char buff[100];
    sprintf(buff, "Stars: %d", GameManager::instance->GetCoinsTotal());
    DrawText(buff, screenWidth / 2, 0, 25, WHITE);

    sprintf(buff, "Stars: %d", GameManager::instance->GetCoinsCarrying());
    DrawText(buff, screenWidth / 2, screenHeight / 2, 25, WHITE);

    sprintf(buff, "Highscore: %d", GameManager::instance->GetCoinsHighscore());
    DrawText(buff, screenWidth / 2, screenHeight / 2 - 50, 25, WHITE);
}

void UIManager::Render(const int screenWidth, const int screenHeight, const float deltaTime)
{
    switch (GameManager::instance->GetGameState())
    {
        case GameManager::GameState::MainMenu: {
            Render_MainMenu(screenWidth, screenHeight, deltaTime);
            break;
        }
        case GameManager::GameState::Playing: {
            Render_Playing(screenWidth, screenHeight, deltaTime);
            break;
        }
        case GameManager::GameState::PlayerDead: {
            Render_PlayerDead(screenWidth, screenHeight, deltaTime);
            break;
        }
    }

    DrawFPS(screenWidth / 4, 0);
}
