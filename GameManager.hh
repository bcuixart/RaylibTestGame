#ifndef GAMEMANAGER_HH
#define GAMEMANAGER_HH

#include <iostream>
#include <random>

#include "raylib.h"
#include "raymath.h"

#include "Player.hh"
#include "Camera.hh"
#include "World.hh"

using namespace std;

class GameManager {
public:
	GameManager();

	enum GameState { MainMenu, Playing, JustDied, Dead };
	GameState GetGameState() const;

	void PrepareGame();

	void Update(const int width, const int height);
	void Render(const int width, const int height);

	void CollectCoin();
	void KillPlayer();

	static GameManager* instance;

protected:

private:

	Player* player;
	CameraManager* camera;
	World* world;

	GameState currentState = MainMenu;

	int coinsTotal = 0;
	int coinsCurrent = 0;
	int coinsHighscore = 0;

	float playerRadius;

	const float PLAYER_DEAD_RETRY_TIME = 1;
	float playerDeadTimeElapsed;

	const bool DEBUG_PRINT_SEED = false;
};

#endif