#include "EffectManager.hh"
#include "GameManager.hh"

EffectManager::EffectManager() 
{

}

void EffectManager::Clear()
{
    effects.clear();
}

void EffectManager::AddCoinCollectedEffect(const Vector2& position) 
{
	effects.push_back({ CoinCollected, 0, position, 0, 0, 0 });
}

void EffectManager::AddDeadCoinMoveEffect(const int quantity, const Vector2& position) 
{
    float angleIncrement = 360.f / quantity;

    for (int i = 0; i < quantity; ++i) 
    {
	    effects.push_back({ 
        DeadCoinMove, 
        0, position, 
        angleIncrement * i * float(DEG_TO_RAD) + (float)GameManager::instance->GetRandomInRange(-20, 20), 
        (float)GameManager::instance->GetRandomInRange(40, 80),
        0});
    }
}

void EffectManager::AddCheckpointCoinMoveEffect(const int quantity, const Vector2& position) 
{
    for (int i = 0; i < quantity; ++i) 
    {
	    effects.push_back({ 
        CheckpointCoinMove, 
        0, position, 
        position.x,
        position.y,
        (float)GameManager::instance->GetRandomInRange(90, 110) / 100.f});
    }
}

bool EffectManager::RenderCoinCollected(Effect& effect, const float deltaTime) 
{
    effect.elapsedLife += deltaTime; 
    if (effect.elapsedLife >= DURATION_COIN_COLLECTED) return true; 
    
    DrawCircle(effect.position.x, effect.position.y, 10, WHITE);

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

    DrawCircle(effect.position.x, effect.position.y, 10, WHITE);

    return false;
}

bool EffectManager::RenderCheckpoinCoinMove(Effect& effect, const float deltaTime, const Vector2& uiCoinPos) 
{
    effect.elapsedLife += deltaTime; 
    if (effect.elapsedLife >= DURATION_COIN_COLLECTED) return true; 

    float lerpValue = (effect.elapsedLife) / (DURATION_CHECKPOINT_COIN_MOVE * effect.parameter3);
    
    effect.position.x = Lerp(effect.parameter1, uiCoinPos.x, lerpValue);
    effect.position.y = Lerp(effect.parameter2, uiCoinPos.y, lerpValue);

    DrawCircle(effect.position.x, effect.position.y, 10, WHITE);

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
