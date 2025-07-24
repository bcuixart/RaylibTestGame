#ifndef WORLD_HH
#define WORLD_HH

#include <iostream>
#include <vector>
#include <map>
#include <set>

#include "raylib.h"
#include "raymath.h"

#include "WorldObject.hh"
#include "Coin.hh"
#include "Obstacle.hh"

using namespace std;

class World {
public:
	World();

	int Update(const Vector2& playerPosition, const float playerRadius);
	void Render();

	void Start(int _seed);
	void ClearWorld();

protected:

private:
	float getRandomNumberFromSeed(int x, int y) const;
	float getRandomNumberBetween(float min, float max, int x, int y) const;

	void LoadUnloadChunks(const Vector2& playerPosition);

	void LoadChunk(const pair<int, int>& chunk);
	void UnloadChunk(const pair<int, int>& chunk);

	void DeleteCoin(const WorldObject* coinToDelete);

	map<pair<int,int>, vector<WorldObject*>> worldObjects;

	int seed;

	// Ha de ser pair<int,int> i no Vector2 perque el compilador plora
	set<pair<int, int>> loadedChunks;
	set<pair<int, int>> collectedCoins;

	Texture coinTexture = LoadTexture("Assets/Coin_001.png");
	Texture obstacleTexture = LoadTexture("Assets/Obstacle_001.png");

	const float CHUNK_SIZE = 500;
	const float CHUNK_OBJECT_SIZE = 150;
	const int PLAYER_LOAD_CHUNK_RADIUS = 2;

	const bool DEBUG_PRINT_CHUNKINFO = false;
};

#endif