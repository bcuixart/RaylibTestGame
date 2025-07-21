#include "World.hh"

World::World(int _seed) 
{
	seed = _seed;
	worldObjects = map<pair<int, int>, vector<WorldObject*>>();
	loadedChunks = set<pair<int, int>>();
}

float World::getRandomNumberFromSeed(int x, int y) const 
{
	unsigned int hash = seed;

	hash ^= static_cast<unsigned int>(x * 1000);
	hash ^= static_cast<unsigned int>(y * 1000);

	hash = (hash ^ (hash >> 16)) * 0x45d9f3b;
	hash = (hash ^ (hash >> 16)) * 0x45d9f3b;
	hash = hash ^ (hash >> 16);

	return (static_cast<float>(hash) / std::numeric_limits<unsigned int>::max());
}

void World::LoadUnloadChunks(const Vector2& playerPosition)
{
	int playerChunkX = int(playerPosition.x / CHUNK_SIZE);
	int playerChunkY = int(playerPosition.y / CHUNK_SIZE);

	int minX = playerChunkX - PLAYER_LOAD_CHUNK_RADIUS;
	int maxX = playerChunkX + PLAYER_LOAD_CHUNK_RADIUS;
	int minY = playerChunkY - PLAYER_LOAD_CHUNK_RADIUS;
	int maxY = playerChunkY + PLAYER_LOAD_CHUNK_RADIUS;

	// Carregar chunks
	for (int x = minX; x <= maxX; ++x) {
		for (int y = minY; y <= maxY; ++y) {

			pair<int, int> chunk = { x, y };
			if (loadedChunks.find(chunk) == loadedChunks.end())
			{
				if (DEBUG_PRINT_CHUNKINFO) std::cout << "Must load a chunk: " << x << ' ' << y << std::endl;

				LoadChunk(chunk);
			}
		}
	}

	// Borrar chunks
	for (auto it = loadedChunks.begin(); it != loadedChunks.end(); )
	{
		pair<int, int> chunk = *it;
		int x = chunk.first;
		int y = chunk.second;
		if (!(x >= minX && x <= maxX && y >= minY && y <= maxY))
		{
			if (DEBUG_PRINT_CHUNKINFO) std::cout << "Must delete a chunk: " << x << ' ' << y << std::endl;
			UnloadChunk(chunk);
			it = loadedChunks.erase(it);
		}
		else {
			++it;
		}
	}
}

void World::LoadChunk(const pair<int, int>& chunk)
{
	loadedChunks.insert(chunk);
	worldObjects[chunk] = vector<WorldObject*>();

	int minX = chunk.first * CHUNK_SIZE - CHUNK_SIZE / 2 + CHUNK_OBJECT_SIZE / 2;
	int maxX = chunk.first * CHUNK_SIZE + CHUNK_SIZE / 2 - CHUNK_OBJECT_SIZE / 2;
	int minY = chunk.second * CHUNK_SIZE - CHUNK_SIZE / 2 + CHUNK_OBJECT_SIZE / 2;
	int maxY = chunk.second * CHUNK_SIZE + CHUNK_SIZE / 2 - CHUNK_OBJECT_SIZE / 2;

	for (int x = minX; x <= maxX; x += CHUNK_OBJECT_SIZE) {
		for (int y = minY; y <= maxY; y += CHUNK_OBJECT_SIZE) {
			float chanceToSpawnObject = getRandomNumberFromSeed(x, y);

			if (chanceToSpawnObject <= 0.1f) 
			{
				worldObjects[chunk].push_back(new Coin({ float(x),float(y) }, 0.f, 1.f));
			}
		}
	}
}

void World::UnloadChunk(const pair<int, int>& chunk)
{
	for (WorldObject* obj : worldObjects[chunk]) {
		delete obj;
	}

	worldObjects[chunk].clear();
}

void World::Update(const Vector2& playerPosition)
{
	LoadUnloadChunks(playerPosition);

	for (auto it = loadedChunks.begin(); it != loadedChunks.end(); ++it)
	{
		pair<int, int> chunk = *it;
		int s = worldObjects[chunk].size();
		for (int i = 0; i < s; ++i) {
			worldObjects[chunk][i]->Update();
		}
	}
}

void World::Render() 
{
	for (auto it = loadedChunks.begin(); it != loadedChunks.end(); ++it)
	{
		pair<int, int> chunk = *it;
		int s = worldObjects[chunk].size();
		for (int i = 0; i < s; ++i) {
			worldObjects[chunk][i]->Render();
		}
	}
}