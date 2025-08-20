#ifndef EFFECTMANAGER_HH
#define EFFECTMANAGER_HH

#include <iostream>
#include <vector>
#include <cmath>

#include <raylib.h>
#include <raymath.h>

#define DEG_TO_RAD  M_PI / 180

using namespace std;

class EffectManager {
public:
	EffectManager();

	void Clear();

	void Render(const int width, const int height, const float deltaTime, const Vector2& cameraPosition);

	void AddCoinCollectedEffect(const Vector2& position, const float rotation, const float scale);
	void AddDeadCoinMoveEffect(const Vector2& position);
	void AddCheckpointCoinMoveEffect(const Vector2& position);

protected:

private:

	enum EffectType { SmokeTrail, Explosion, CoinCollected, CheckpointCoinMove, DeadCoinMove };
	struct Effect 
	{
		EffectType type;

		float elapsedLife = 0;

		Vector2 position;

		float parameter1 = 0;
		float parameter2 = 0;
		float parameter3 = 0;
		float parameter4 = 0;
	};

	void DrawEffectTexture(const Texture& texture, const Vector2& position, const float rotation, const float scale, const Color& color);

	bool RenderCoinCollected(Effect& effect, const float deltaTime);
	bool RenderDeadCoinMove(Effect& effect, const float deltaTime);
	bool RenderCheckpoinCoinMove(Effect& effect, const float deltaTime, const Vector2& uiCoinPos);

	vector<Effect> effects;

	vector<float> sizesForCoinEffects;

	const Texture coinTexture = LoadTexture("Assets/Textures/Coin_001.png");

	const float DURATION_COIN_COLLECTED = 1;
	const float DURATION_CHECKPOINT_COIN_MOVE = 1;

	const bool DEBUG_DRAW_EFFECT_RADIUS = false;
};

#endif