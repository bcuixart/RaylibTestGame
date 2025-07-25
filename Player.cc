#include "Player.hh"

Player::Player() 
{
	Start();
}

Vector2 Player::getPlayerPosition() const {
	return playerPosition;
}

float Player::getPlayerRadius() const {
	return HITBOX_RADIUS;
}

void Player::Start() 
{
	currentState = WaitingToStart;

	playerVelocity.x = 0;
	playerVelocity.y = 0;

	playerPosition.x = 0;
	playerPosition.y = 0;
	playerRotation = 90;

	playerPositionMain = playerPosition;
	playerPositionWindow = playerPosition;
	playerPositionPropeller000 = playerPosition;
	playerPositionPropeller001 = playerPosition;
	playerPositionPropeller002 = playerPosition;
	playerPositionTop = playerPosition;

	playerDeadDebrisSpeedMultiplier = 1;
}

void Player::KillPlayer() 
{
	if (currentState == Playing) {
		playerDeadElapsed = 0;
		playerDeadPosition = playerPosition;

		currentState = JustDied;
	}
}

void Player::DeadMoveDebris(float deltaTime)
{
	playerPositionMain.x += playerVelocity.x * deltaTime;
	playerPositionMain.y -= playerVelocity.y * deltaTime;
	playerPositionWindow.x += playerVelocity.x * deltaTime;
	playerPositionWindow.y -= playerVelocity.y * deltaTime;
	playerPositionTop.x += playerVelocity.x * deltaTime * 1.25f;
	playerPositionTop.y -= playerVelocity.y * deltaTime * 1.25f;
	playerPositionPropeller000.x -= playerVelocity.y * deltaTime;
	playerPositionPropeller000.y -= playerVelocity.x * deltaTime;
	playerPositionPropeller001.x -= playerVelocity.x * deltaTime;
	playerPositionPropeller001.y += playerVelocity.y * deltaTime;
	playerPositionPropeller002.x += playerVelocity.y * deltaTime;
	playerPositionPropeller002.y += playerVelocity.x * deltaTime;
}

int Player::Update(float deltaTime)
{
	if (currentState == JustDied)
	{
		currentFireTexture = -1;

		playerDeadElapsed += deltaTime;
		if (playerDeadElapsed >= PLAYER_DEAD_RETRY_TIME) currentState = Dead;

		DeadMoveDebris(deltaTime * playerDeadDebrisSpeedMultiplier);
		playerDeadDebrisSpeedMultiplier = max(playerDeadDebrisSpeedMultiplier - PLAYER_DEAD_DECELERATION * deltaTime, PLAYER_DEAD_MIN_SPEED);

		return 0;
	}

	if (currentState == Dead) 
	{
		playerDeadElapsed += deltaTime;

		DeadMoveDebris(deltaTime * playerDeadDebrisSpeedMultiplier);
		playerDeadDebrisSpeedMultiplier = max(playerDeadDebrisSpeedMultiplier - PLAYER_DEAD_DECELERATION * deltaTime, PLAYER_DEAD_MIN_SPEED);

		if (IsKeyPressed(KEY_SPACE)) return 1;
		return 0;
	}

	if (currentState == WaitingToStart) 
	{
		currentFireTexture = -1;
		if (!IsKeyPressed(KEY_SPACE)) return 0;
		currentState = Playing;
	}

	float rotationSin = std::sin(playerRotation * DEG_TO_RAD);
	float rotationCos = std::cos(playerRotation * DEG_TO_RAD);

	if (IsKeyDown(KEY_SPACE))
	{
		playerVelocity.x += ACCELERATION * rotationCos * deltaTime;
		playerVelocity.y += ACCELERATION * rotationSin * deltaTime;

		if (currentFireTexture == -1) currentFireTexture = 0;
		currentFireTexture = currentFireTexture + FIRE_TEXTURE_SPEED * deltaTime;
		if (currentFireTexture > (float)FIRE_TEXTURES) currentFireTexture = (float)FIRE_ACCELERATE_TEXTURES;
	}
	else
	{
		playerRotation = std::fmod(playerRotation + ROTATE_SPEED * deltaTime, 360.f);

		if (currentFireTexture > (float)FIRE_ACCELERATE_TEXTURES) currentFireTexture = FIRE_ACCELERATE_TEXTURES;
		currentFireTexture = currentFireTexture - FIRE_TEXTURE_SPEED * deltaTime;
		if (currentFireTexture <= 0) currentFireTexture = -1;
	}

	if (DEBUG_PRINT_FIRE_TEXTURE) std::cout << currentFireTexture << std::endl;

	float speed = std::sqrt(playerVelocity.x * playerVelocity.x + playerVelocity.y * playerVelocity.y);
	if (speed > 0)
	{
		playerVelocity.x += -playerVelocity.x / speed * DECELERATION * deltaTime;
		playerVelocity.y += -playerVelocity.y / speed * DECELERATION * deltaTime;

		float newSpeed = std::sqrt(playerVelocity.x * playerVelocity.x + playerVelocity.y * playerVelocity.y);
		speed = newSpeed;
		if (newSpeed < DECELERATION_STOP_TOLERANCE)
		{
			playerVelocity = { 0.0f, 0.0f };
		}
	}

	if (speed > MAX_PLAYER_SPEED)
	{
		playerVelocity.x = (playerVelocity.x / speed) * MAX_PLAYER_SPEED;
		playerVelocity.y = (playerVelocity.y / speed) * MAX_PLAYER_SPEED;
	}

	playerPosition.x += playerVelocity.x * deltaTime;
	playerPosition.y -= playerVelocity.y * deltaTime;

	playerPositionMain = playerPosition;
	playerPositionWindow = playerPosition;
	playerPositionPropeller000 = playerPosition;
	playerPositionPropeller001 = playerPosition;
	playerPositionPropeller002 = playerPosition;
	playerPositionTop = playerPosition;

	if (DEBUG_PRINT_ROT) std::cout << playerRotation << std::endl;
	if (DEBUG_PRINT_POS) std::cout << playerPosition.x << ' ' << playerPosition.y << std::endl;
	if (DEBUG_PRINT_VEL) std::cout << playerVelocity.x << ' ' << playerVelocity.y << std::endl;

	return 0;
}

void Player::Render() 
{
	Rectangle source = { 0.0f, 0.0f, (float)textureWidth, (float)textureHeight };
	Rectangle destMain = { playerPositionMain.x, playerPositionMain.y, (float)textureWidth / 8, (float)textureHeight / 8 };
	Rectangle destWindow = { playerPositionWindow.x, playerPositionWindow.y, (float)textureWidth / 8, (float)textureHeight / 8 };
	Rectangle destPropeller000 = { playerPositionPropeller000.x, playerPositionPropeller000.y, (float)textureWidth / 8, (float)textureHeight / 8 };
	Rectangle destPropeller001 = { playerPositionPropeller001.x, playerPositionPropeller001.y, (float)textureWidth / 8, (float)textureHeight / 8 };
	Rectangle destPropeller002 = { playerPositionPropeller002.x, playerPositionPropeller002.y, (float)textureWidth / 8, (float)textureHeight / 8 };
	Rectangle destTop = { playerPositionTop.x, playerPositionTop.y, (float)textureWidth / 8, (float)textureHeight / 8 };
	Vector2 origin = { (float)textureWidth * 1 / 16, (float)textureHeight * 1 / 16 };

	DrawTexturePro(playerBodyMainTexture, source, destMain, origin, -playerRotation + 90, playerBodyColorLight);
	DrawTexturePro(playerBodyWindowTexture, source, destWindow, origin, -playerRotation + 90, playerBodyColorDark);
	DrawTexturePro(playerBodyPropeller000Texture, source, destPropeller000, origin, -playerRotation + 90, playerBodyColorDark);
	DrawTexturePro(playerBodyPropeller001Texture, source, destPropeller001, origin, -playerRotation + 90, playerBodyColorDark);
	DrawTexturePro(playerBodyPropeller002Texture, source, destPropeller002, origin, -playerRotation + 90, playerBodyColorDark);
	DrawTexturePro(playerBodyTopTexture, source, destTop, origin, -playerRotation + 90, playerBodyColorDark);
	if (currentFireTexture != -1) DrawTexturePro(fireTextures[(int)currentFireTexture], source, destMain, origin, -playerRotation + 90, playerFireColor);

	if (drawDirectionPoints) 
	{
		float rotationSin = std::sin((-playerRotation) * DEG_TO_RAD);
		float rotationCos = std::cos((-playerRotation) * DEG_TO_RAD);

		Vector2 directionPoint1 = {
			playerPosition.x + 20 * rotationCos,
			playerPosition.y + 20 * rotationSin
		};

		Vector2 directionPoint2 = {
			playerPosition.x + 30 * rotationCos,
			playerPosition.y + 30 * rotationSin
		};

		Vector2 directionPoint3 = {
			playerPosition.x + 40 * rotationCos,
			playerPosition.y + 40 * rotationSin
		};

		DrawCircle(directionPoint1.x, directionPoint1.y, 1.5f, WHITE);
		DrawCircle(directionPoint2.x, directionPoint2.y, 1.5f, WHITE);
		DrawCircle(directionPoint3.x, directionPoint3.y, 1.25f, GRAY);
	}

	if (DEBUG_SHOW_HITBOX) DrawCircleLines(playerPosition.x, playerPosition.y, HITBOX_RADIUS, BLUE);
}