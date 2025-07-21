#include "World.hh"

World::World(int _seed) 
{
	seed = _seed;
	worldObjects = vector<WorldObject>();
}

float World::getRandomNumberFromSeed(const Vector2& pos) const 
{
	unsigned int hash = seed;

	hash ^= static_cast<unsigned int>(pos.x * 1000);
	hash ^= static_cast<unsigned int>(pos.y * 1000);

	hash = (hash ^ (hash >> 16)) * 0x45d9f3b;
	hash = (hash ^ (hash >> 16)) * 0x45d9f3b;
	hash = hash ^ (hash >> 16);

	return (static_cast<float>(hash) / std::numeric_limits<unsigned int>::max());
}

void World::Update(const Vector2& playerPosition)
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
				std::cout << "Must load a chunk: " << x << ' ' << y << std::endl;
				loadedChunks.insert(chunk);
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
			std::cout << "Must delete a chunk: " << x << ' ' << y << std::endl;
			it = loadedChunks.erase(it);
		}
		else {
			++it;
		}
	}
}

void World::Render() 
{

}