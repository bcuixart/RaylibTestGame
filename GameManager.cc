#include "GameManager.hh"

GameManager* GameManager::instance = nullptr;

GameManager::GameManager() 
{
	GameManager::instance = this;

	player = new Player();
	camera = new CameraManager();
	world = new World();

	playerRadius = player->getPlayerRadius();

	StartGame();
}

void GameManager::KillPlayer() 
{
	player->KillPlayer();
}

void GameManager::StartGame() 
{
	world->ClearWorld();

	std::random_device rd;
	std::mt19937 gen(rd());

	unsigned int randomSeed = static_cast<unsigned int>(gen());
	if (DEBUG_PRINT_SEED) std::cout << "Seed:" << randomSeed << std::endl;

	world->Start(randomSeed);
	player->Start();
	camera->Start();
}

void GameManager::Update() 
{
	float deltaTime = GetFrameTime();

	player->Update(deltaTime);
	world->Update(player->getPlayerPosition(), playerRadius, deltaTime);
	camera->Update(player->getPlayerPosition(), GetScreenWidth(), GetScreenHeight(), deltaTime);
}

void GameManager::Render() 
{
	ClearBackground({ 133, 60, 217, 255 });
	BeginDrawing();

	camera->MBeginMode2D();

	world->Render();
	player->Render();

	EndDrawing();
	EndMode2D();

	DrawFPS(0, 0);
}