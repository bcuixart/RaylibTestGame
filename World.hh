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

using namespace std;

class World {
public:
	World(int _seed);

	void Update(const Vector2& playerPosition);
	void Render();

protected:

private:
	float getRandomNumberFromSeed(int x, int y) const;

	void LoadUnloadChunks(const Vector2& playerPosition);

	void LoadChunk(const pair<int, int>& chunk);
	void UnloadChunk(const pair<int, int>& chunk);

	map<pair<int,int>, vector<WorldObject*>> worldObjects;

	int seed;

	// Ha de ser pair<int,int> i no Vector2 perque el compilador plora
	set<pair<int, int>> loadedChunks;

	const float CHUNK_SIZE = 500;
	const float CHUNK_OBJECT_SIZE = 100;
	const int PLAYER_LOAD_CHUNK_RADIUS = 2;

	const bool DEBUG_PRINT_CHUNKINFO = false;
};

#endif