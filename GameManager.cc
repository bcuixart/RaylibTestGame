#include "GameManager.hh"

GameManager* GameManager::instance = nullptr;

GameManager::GameManager() 
{
	GameManager::instance = this;

	player = new Player();
	camera = new CameraManager();
	world = new World();

	playerRadius = player->getPlayerRadius();

	currentState = MainMenu;
	PrepareGame();
}

GameManager::GameState GameManager::GetGameState() const 
{
	return currentState;
}

void GameManager::CollectCoin() 
{
	++coinsCurrent;
}

void GameManager::KillPlayer() 
{
	if (currentState == Playing) 
	{
		player->KillPlayer();

		playerDeadTimeElapsed = 0;
		currentState = JustDied;

		coinsTotal += coinsCurrent;
		if (coinsCurrent > coinsHighscore) coinsHighscore = coinsCurrent;
	}
}

void GameManager::PrepareGame() 
{
	world->ClearWorld();

	std::random_device rd;
	std::mt19937 gen(rd());

	unsigned int randomSeed = static_cast<unsigned int>(gen());
	if (DEBUG_PRINT_SEED) std::cout << "Seed:" << randomSeed << std::endl;

	world->Start(randomSeed);
	player->Start();
	camera->Start();

	coinsCurrent = 0;
}

void GameManager::Update(const int width, const int height) 
{
	float deltaTime = GetFrameTime();

	switch (currentState) 
	{
		case MainMenu: {
			if (IsKeyPressed(KEY_SPACE)) currentState = Playing;
			break;
		}
		case Playing: {
			break;
		}
		case JustDied: {
			playerDeadTimeElapsed += deltaTime;
			if (playerDeadTimeElapsed >= PLAYER_DEAD_RETRY_TIME) currentState = Dead;
			break;
		}
		case Dead: {
			if (IsKeyPressed(KEY_SPACE)) {
				PrepareGame();
				currentState = MainMenu;
			}
			break;
		}
	}

	player->Update(deltaTime);
	world->Update(player->getPlayerPosition(), playerRadius, deltaTime);
	camera->Update(player->getPlayerPosition(), width, height, deltaTime);
}

void GameManager::Render(const int width, const int height) 
{
	ClearBackground({ 133, 60, 217, 255 });
	BeginDrawing();

	camera->MBeginMode2D();

	world->Render();
	player->Render();

	EndDrawing();
	EndMode2D();

	char buff[100];
	sprintf(buff, "Coins: %d", coinsCurrent);
	DrawText(buff, width / 2, 0, 25, WHITE);

	DrawFPS(0, 0);
}