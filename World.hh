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

	int Update(const Vector2& playerPosition, const float playerRadius, const float deltaTime);
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

	const float CHUNK_SIZE = 500;
	const float CHUNK_OBJECT_SIZE = 150;
	const int PLAYER_LOAD_CHUNK_RADIUS = 2;

	const Texture coinTexture = LoadTexture("Assets/Textures/Coin_001.png");
	const vector<Texture> obstacleTextures = { 
		LoadTexture("Assets/Textures/Asteroid/Obstacle_Asteroid_001.png"),
		LoadTexture("Assets/Textures/Asteroid/Obstacle_Asteroid_002.png"),
		LoadTexture("Assets/Textures/Asteroid/Obstacle_Asteroid_003.png"),
		LoadTexture("Assets/Textures/Asteroid/Obstacle_Asteroid_004.png"),
		LoadTexture("Assets/Textures/Asteroid/Obstacle_Asteroid_005.png"),
		LoadTexture("Assets/Textures/Asteroid/Obstacle_Asteroid_006.png"),
		LoadTexture("Assets/Textures/Asteroid/Obstacle_Asteroid_007.png"),
		LoadTexture("Assets/Textures/Asteroid/Obstacle_Asteroid_008.png"),
		LoadTexture("Assets/Textures/Asteroid/Obstacle_Asteroid_009.png"),
		LoadTexture("Assets/Textures/Asteroid/Obstacle_Asteroid_010.png"),
		LoadTexture("Assets/Textures/Asteroid/Obstacle_Asteroid_011.png"),
		LoadTexture("Assets/Textures/Asteroid/Obstacle_Asteroid_012.png"),
		LoadTexture("Assets/Textures/Asteroid/Obstacle_Asteroid_013.png"),
		LoadTexture("Assets/Textures/Asteroid/Obstacle_Asteroid_014.png"),
		LoadTexture("Assets/Textures/Asteroid/Obstacle_Asteroid_015.png"),
		LoadTexture("Assets/Textures/Asteroid/Obstacle_Asteroid_016.png"),
		LoadTexture("Assets/Textures/Asteroid/Obstacle_Asteroid_017.png"),
		LoadTexture("Assets/Textures/Asteroid/Obstacle_Asteroid_018.png"),
		LoadTexture("Assets/Textures/Asteroid/Obstacle_Asteroid_019.png"),
		LoadTexture("Assets/Textures/Asteroid/Obstacle_Asteroid_020.png"),
		LoadTexture("Assets/Textures/Asteroid/Obstacle_Asteroid_021.png"),
		LoadTexture("Assets/Textures/Asteroid/Obstacle_Asteroid_022.png"),
		LoadTexture("Assets/Textures/Asteroid/Obstacle_Asteroid_023.png"),
		LoadTexture("Assets/Textures/Asteroid/Obstacle_Asteroid_024.png"),
		LoadTexture("Assets/Textures/Asteroid/Obstacle_Asteroid_025.png"),
		LoadTexture("Assets/Textures/Asteroid/Obstacle_Asteroid_026.png"),
		LoadTexture("Assets/Textures/Asteroid/Obstacle_Asteroid_027.png"),
		LoadTexture("Assets/Textures/Asteroid/Obstacle_Asteroid_028.png"),
		LoadTexture("Assets/Textures/Asteroid/Obstacle_Asteroid_029.png"),
		LoadTexture("Assets/Textures/Asteroid/Obstacle_Asteroid_030.png"),
		LoadTexture("Assets/Textures/Asteroid/Obstacle_Asteroid_031.png"),
		LoadTexture("Assets/Textures/Asteroid/Obstacle_Asteroid_032.png"),
		LoadTexture("Assets/Textures/Asteroid/Obstacle_Asteroid_033.png"),
		LoadTexture("Assets/Textures/Asteroid/Obstacle_Asteroid_034.png"),
		LoadTexture("Assets/Textures/Asteroid/Obstacle_Asteroid_035.png"),
		LoadTexture("Assets/Textures/Asteroid/Obstacle_Asteroid_036.png"),
		LoadTexture("Assets/Textures/Asteroid/Obstacle_Asteroid_037.png"),
		LoadTexture("Assets/Textures/Asteroid/Obstacle_Asteroid_038.png"),
		LoadTexture("Assets/Textures/Asteroid/Obstacle_Asteroid_039.png"),
		LoadTexture("Assets/Textures/Asteroid/Obstacle_Asteroid_040.png"),
		LoadTexture("Assets/Textures/Asteroid/Obstacle_Asteroid_041.png"),
		LoadTexture("Assets/Textures/Asteroid/Obstacle_Asteroid_042.png"),
		LoadTexture("Assets/Textures/Asteroid/Obstacle_Asteroid_043.png"),
		LoadTexture("Assets/Textures/Asteroid/Obstacle_Asteroid_044.png"),
		LoadTexture("Assets/Textures/Asteroid/Obstacle_Asteroid_045.png"),
		LoadTexture("Assets/Textures/Asteroid/Obstacle_Asteroid_046.png"),
		LoadTexture("Assets/Textures/Asteroid/Obstacle_Asteroid_047.png"),
		LoadTexture("Assets/Textures/Asteroid/Obstacle_Asteroid_048.png"),
		LoadTexture("Assets/Textures/Asteroid/Obstacle_Asteroid_049.png"),
		LoadTexture("Assets/Textures/Asteroid/Obstacle_Asteroid_050.png"),
		LoadTexture("Assets/Textures/Asteroid/Obstacle_Asteroid_051.png"),
		LoadTexture("Assets/Textures/Asteroid/Obstacle_Asteroid_052.png"),
		LoadTexture("Assets/Textures/Asteroid/Obstacle_Asteroid_053.png"),
		LoadTexture("Assets/Textures/Asteroid/Obstacle_Asteroid_054.png"),
		LoadTexture("Assets/Textures/Asteroid/Obstacle_Asteroid_055.png"),
		LoadTexture("Assets/Textures/Asteroid/Obstacle_Asteroid_056.png"),
		LoadTexture("Assets/Textures/Asteroid/Obstacle_Asteroid_057.png"),
		LoadTexture("Assets/Textures/Asteroid/Obstacle_Asteroid_058.png"),
		LoadTexture("Assets/Textures/Asteroid/Obstacle_Asteroid_059.png"),
		LoadTexture("Assets/Textures/Asteroid/Obstacle_Asteroid_060.png"),
		LoadTexture("Assets/Textures/Asteroid/Obstacle_Asteroid_061.png"),
		LoadTexture("Assets/Textures/Asteroid/Obstacle_Asteroid_062.png"),
		LoadTexture("Assets/Textures/Asteroid/Obstacle_Asteroid_063.png"),
		LoadTexture("Assets/Textures/Asteroid/Obstacle_Asteroid_064.png"),
		LoadTexture("Assets/Textures/Asteroid/Obstacle_Asteroid_065.png"),
		LoadTexture("Assets/Textures/Asteroid/Obstacle_Asteroid_066.png"),
		LoadTexture("Assets/Textures/Asteroid/Obstacle_Asteroid_067.png"),
		LoadTexture("Assets/Textures/Asteroid/Obstacle_Asteroid_068.png"),
		LoadTexture("Assets/Textures/Asteroid/Obstacle_Asteroid_069.png"),
		LoadTexture("Assets/Textures/Asteroid/Obstacle_Asteroid_070.png"),
		LoadTexture("Assets/Textures/Asteroid/Obstacle_Asteroid_071.png"),
		LoadTexture("Assets/Textures/Asteroid/Obstacle_Asteroid_072.png"),
		LoadTexture("Assets/Textures/Asteroid/Obstacle_Asteroid_073.png"),
		LoadTexture("Assets/Textures/Asteroid/Obstacle_Asteroid_074.png"),
		LoadTexture("Assets/Textures/Asteroid/Obstacle_Asteroid_075.png"),
		LoadTexture("Assets/Textures/Asteroid/Obstacle_Asteroid_076.png"),
		LoadTexture("Assets/Textures/Asteroid/Obstacle_Asteroid_077.png"),
		LoadTexture("Assets/Textures/Asteroid/Obstacle_Asteroid_078.png"),
		LoadTexture("Assets/Textures/Asteroid/Obstacle_Asteroid_079.png"),
		LoadTexture("Assets/Textures/Asteroid/Obstacle_Asteroid_080.png"),
		LoadTexture("Assets/Textures/Asteroid/Obstacle_Asteroid_081.png"),
		LoadTexture("Assets/Textures/Asteroid/Obstacle_Asteroid_082.png"),
		LoadTexture("Assets/Textures/Asteroid/Obstacle_Asteroid_083.png"),
		LoadTexture("Assets/Textures/Asteroid/Obstacle_Asteroid_084.png"),
		LoadTexture("Assets/Textures/Asteroid/Obstacle_Asteroid_085.png"),
		LoadTexture("Assets/Textures/Asteroid/Obstacle_Asteroid_086.png"),
		LoadTexture("Assets/Textures/Asteroid/Obstacle_Asteroid_087.png"),
		LoadTexture("Assets/Textures/Asteroid/Obstacle_Asteroid_088.png"),
		LoadTexture("Assets/Textures/Asteroid/Obstacle_Asteroid_089.png"),
		LoadTexture("Assets/Textures/Asteroid/Obstacle_Asteroid_090.png"),
		LoadTexture("Assets/Textures/Asteroid/Obstacle_Asteroid_091.png"),
		LoadTexture("Assets/Textures/Asteroid/Obstacle_Asteroid_092.png"),
		LoadTexture("Assets/Textures/Asteroid/Obstacle_Asteroid_093.png"),
		LoadTexture("Assets/Textures/Asteroid/Obstacle_Asteroid_094.png"),
		LoadTexture("Assets/Textures/Asteroid/Obstacle_Asteroid_095.png"),
		LoadTexture("Assets/Textures/Asteroid/Obstacle_Asteroid_096.png"),
		LoadTexture("Assets/Textures/Asteroid/Obstacle_Asteroid_097.png"),
		LoadTexture("Assets/Textures/Asteroid/Obstacle_Asteroid_098.png"),
		LoadTexture("Assets/Textures/Asteroid/Obstacle_Asteroid_099.png"),
		LoadTexture("Assets/Textures/Asteroid/Obstacle_Asteroid_100.png"),
		LoadTexture("Assets/Textures/Asteroid/Obstacle_Asteroid_101.png"),
		LoadTexture("Assets/Textures/Asteroid/Obstacle_Asteroid_102.png"),
		LoadTexture("Assets/Textures/Asteroid/Obstacle_Asteroid_103.png"),
		LoadTexture("Assets/Textures/Asteroid/Obstacle_Asteroid_104.png"),
		LoadTexture("Assets/Textures/Asteroid/Obstacle_Asteroid_105.png"),
		LoadTexture("Assets/Textures/Asteroid/Obstacle_Asteroid_106.png"),
		LoadTexture("Assets/Textures/Asteroid/Obstacle_Asteroid_107.png"),
		LoadTexture("Assets/Textures/Asteroid/Obstacle_Asteroid_108.png"),
		LoadTexture("Assets/Textures/Asteroid/Obstacle_Asteroid_109.png"),
		LoadTexture("Assets/Textures/Asteroid/Obstacle_Asteroid_110.png"),
		LoadTexture("Assets/Textures/Asteroid/Obstacle_Asteroid_111.png"),
		LoadTexture("Assets/Textures/Asteroid/Obstacle_Asteroid_112.png"),
		LoadTexture("Assets/Textures/Asteroid/Obstacle_Asteroid_113.png"),
		LoadTexture("Assets/Textures/Asteroid/Obstacle_Asteroid_114.png"),
		LoadTexture("Assets/Textures/Asteroid/Obstacle_Asteroid_115.png"),
		LoadTexture("Assets/Textures/Asteroid/Obstacle_Asteroid_116.png"),
		LoadTexture("Assets/Textures/Asteroid/Obstacle_Asteroid_117.png"),
		LoadTexture("Assets/Textures/Asteroid/Obstacle_Asteroid_118.png"),
		LoadTexture("Assets/Textures/Asteroid/Obstacle_Asteroid_119.png"),
		LoadTexture("Assets/Textures/Asteroid/Obstacle_Asteroid_120.png"),
	
	};

	const bool DEBUG_PRINT_CHUNKINFO = false;
};

#endif