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

	currentPlayerTexture = 0;
}

void Player::KillPlayer() 
{
	currentState = Dead;
}

int Player::Update(float deltaTime)
{
	if (currentState == Dead) 
	{
		if (IsKeyPressed(KEY_SPACE)) return 1;
		return 0;
	}

	if (currentState == WaitingToStart) 
	{
		if (!IsKeyPressed(KEY_SPACE)) return 0;
		currentState = Playing;
	}

	float rotationSin = std::sin(playerRotation * DEG_TO_RAD);
	float rotationCos = std::cos(playerRotation * DEG_TO_RAD);

	if (IsKeyDown(KEY_SPACE))
	{
		playerVelocity.x += ACCELERATION * rotationCos * deltaTime;
		playerVelocity.y += ACCELERATION * rotationSin * deltaTime;

		currentPlayerTexture = 1;
	}
	else
	{
		playerRotation = std::fmod(playerRotation + ROTATE_SPEED * deltaTime, 360.f);

		currentPlayerTexture = 0;
	}

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

	if (DEBUG_PRINT_ROT) std::cout << playerRotation << std::endl;
	if (DEBUG_PRINT_POS) std::cout << playerPosition.x << ' ' << playerPosition.y << std::endl;
	if (DEBUG_PRINT_VEL) std::cout << playerVelocity.x << ' ' << playerVelocity.y << std::endl;

	return 0;
}

void Player::Render() 
{
	DrawTexturePro(
		playerTextures[currentPlayerTexture],
		(Rectangle) { 0.0f, 0.0f, (float)textureWidth, (float)textureHeight },
		(Rectangle) { playerPosition.x, playerPosition.y, (float)textureWidth / 4, (float)textureHeight / 4},
		(Vector2) { (float)textureWidth * 1 / 8, (float)textureHeight * 1 / 8 },
		-playerRotation + 90,
		WHITE
	);

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