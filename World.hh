#ifndef WORLD_HH
#define WORLD_HH

#include <iostream>
#include <vector>
#include <set>

#include "raylib.h"
#include "raymath.h"

#include "WorldObject.hh"

using namespace std;

class World {
public:
	World(int _seed);

	void Update(const Vector2& playerPosition);
	void Render();

protected:

private:
	float getRandomNumberFromSeed(const Vector2& pos) const;

	vector<WorldObject> worldObjects;

	int seed;

	// Ha de ser pair<int,int> i no Vector2 perque el compilador plora
	set<pair<int, int>> loadedChunks;

	const float CHUNK_SIZE = 500;
	const int PLAYER_LOAD_CHUNK_RADIUS = 2;
};

#endif