#include "GameManager.hh"

GameManager::GameManager() 
{
	playerRadius = player.getPlayerRadius();

	StartGame();
}

void GameManager::StartGame() 
{
	std::random_device rd;
	std::mt19937 gen(rd());

	unsigned int randomSeed = static_cast<unsigned int>(gen());
	if (DEBUG_PRINT_SEED) std::cout << "Seed:" << randomSeed << std::endl;

	world.ClearWorld();
	world.Start(randomSeed);
	player.Start();
	camera.Start();
}

void GameManager::Update() 
{
	float deltaTime = GetFrameTime();

	int playerInfo = player.Update(deltaTime);
	if (playerInfo == 1) {
		StartGame(); // Restart if dead
	}

	int playerDied = world.Update(player.getPlayerPosition(), playerRadius, deltaTime);
	if (playerDied) player.KillPlayer();

	camera.Update(player.getPlayerPosition(), GetScreenWidth(), GetScreenHeight(), deltaTime);
}

void GameManager::Render() 
{
	ClearBackground({ 133, 60, 217, 255 });
	BeginDrawing();

	camera.MBeginMode2D();

	world.Render();
	player.Render();

	EndDrawing();
	EndMode2D();

	DrawFPS(0, 0);
}