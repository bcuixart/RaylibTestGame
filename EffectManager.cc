#include "EffectManager.hh"
#include "GameManager.hh"

EffectManager::EffectManager() 
{

}

void EffectManager::Clear()
{
    effects.clear();
}

void EffectManager::AddCoinCollectedEffect(const Vector2& position, const float rotation, const float scale) 
{
	effects.push_back({ CoinCollected, 0, position, rotation, scale, 0, 0 });

    sizesForCoinEffects.push_back(scale);
}

void EffectManager::AddDeadCoinMoveEffect(const Vector2& position) 
{
    int quantity = sizesForCoinEffects.size();

    float angleIncrement = 360.f / quantity;

    for (int i = 0; i < quantity; ++i) 
    {
	    effects.push_back({ 
        DeadCoinMove, 
        0, 
        position, 
        angleIncrement * i * float(DEG_TO_RAD) + (float)GameManager::instance->GetRandomInRange(-20, 20), 
        (float)GameManager::instance->GetRandomInRange(40, 80),
        float(DEG_TO_RAD) * (float)GameManager::instance->GetRandomInRange(0, 360),
        sizesForCoinEffects[i]
        });
    }

    sizesForCoinEffects.clear();
}

void EffectManager::AddCheckpointCoinMoveEffect(const Vector2& position) 
{
    int quantity = sizesForCoinEffects.size();

    for (int i = 0; i < quantity; ++i) 
    {
	    effects.push_back({ 
        CheckpointCoinMove, 
        0, position, 
        position.x,
        position.y,
        (float)GameManager::instance->GetRandomInRange(90, 110) / 100.f,
        sizesForCoinEffects[i]}
        );
    }

    sizesForCoinEffects.clear();
}

void EffectManager::DrawEffectTexture(const Texture& texture, const Vector2& position, const float rotation, const float scale, const Color& color) 
{
	Rectangle sourceRec = { 0.0f, 0.0f, (float)texture.width, (float)texture.height };
	Rectangle destRec = {
		position.x,
		position.y,
		(float)texture.width * scale,
		(float)texture.height * scale
	};
	Vector2 origin = {
		(float)texture.width * scale / 2,
		(float)texture.height * scale / 2
	};
	DrawTexturePro(texture, sourceRec, destRec, origin, rotation, color);
}

bool EffectManager::RenderCoinCollected(Effect& effect, const float deltaTime) 
{
    effect.elapsedLife += deltaTime; 
    if (effect.elapsedLife >= DURATION_COIN_COLLECTED) return true; 
    
    DrawEffectTexture(coinTexture, effect.position, effect.parameter1, effect.parameter2, GameManager::instance->colorManager->GetCoinColor());

    if (DEBUG_DRAW_EFFECT_RADIUS) DrawCircleLines(effect.position.x, effect.position.y, 10, WHITE);

    return false;
}

bool EffectManager::RenderDeadCoinMove(Effect& effect, const float deltaTime) 
{
    effect.elapsedLife += deltaTime; 
    
    float sin = std::sin(effect.parameter1);
    float cos = std::cos(effect.parameter1);

    float speed = max(effect.parameter2 - 1.f * effect.elapsedLife, 0.1f);

    effect.position.x += cos * speed * deltaTime;
    effect.position.y += sin * speed * deltaTime;

    effect.parameter3 += effect.parameter2 * deltaTime;

    DrawEffectTexture(coinTexture, effect.position, effect.parameter3, effect.parameter4, GameManager::instance->colorManager->GetCoinColor());

    if (DEBUG_DRAW_EFFECT_RADIUS) DrawCircleLines(effect.position.x, effect.position.y, 10, WHITE);

    return false;
}

bool EffectManager::RenderCheckpoinCoinMove(Effect& effect, const float deltaTime, const Vector2& uiCoinPos) 
{
    effect.elapsedLife += deltaTime; 
    if (effect.elapsedLife >= DURATION_COIN_COLLECTED * effect.parameter3) {
        GameManager::instance->AddUITotalCoin();
        return true; 
    }

    float lerpValue = (effect.elapsedLife) / (DURATION_CHECKPOINT_COIN_MOVE * effect.parameter3);
    float scaleMultiplier = -4*(lerpValue)*(lerpValue - 1);
    
    effect.position.x = Lerp(effect.parameter1, uiCoinPos.x, lerpValue);
    effect.position.y = Lerp(effect.parameter2, uiCoinPos.y, lerpValue);

    DrawEffectTexture(coinTexture, effect.position, 0, effect.parameter4 * scaleMultiplier, GameManager::instance->colorManager->GetCoinColor());

    if (DEBUG_DRAW_EFFECT_RADIUS) DrawCircleLines(effect.position.x, effect.position.y, 10, WHITE);

    return false;
}

void EffectManager::Render(const int width, const int height, const float deltaTime, const Vector2& cameraPosition)
{
    Vector2 uiCoinPos = { cameraPosition.x + float(width / 2) - 55.f, cameraPosition.y - float(height / 2) + 5.f};

    for (auto it = effects.begin(); it != effects.end(); )
    {
        bool mustDisappear = false;

        switch (it->type) {
            case CoinCollected: {
                mustDisappear = RenderCoinCollected(*it, deltaTime);
                break;
            }
            case SmokeTrail: {
                break;
            }
            case Explosion: {
                break;
            }
            case CheckpointCoinMove: {
                mustDisappear = RenderCheckpoinCoinMove(*it, deltaTime, uiCoinPos);
                break;
            }
            case DeadCoinMove: {
                mustDisappear = RenderDeadCoinMove(*it, deltaTime);
                break;
            }
        }

        if (mustDisappear) it = effects.erase(it);
        else ++it;
    }
}
