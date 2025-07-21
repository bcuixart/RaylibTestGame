#include "Player.hh"

Player::Player() 
{

}

Vector2 Player::getPlayerPosition() const {
	return playerPosition;
}

void Player::Update(float deltaTime)
{
	float rotationSin = std::sin(playerRotation * DEG_TO_RAD);
	float rotationCos = std::cos(playerRotation * DEG_TO_RAD);

	if (IsKeyDown(KEY_SPACE))
	{
		playerVelocity.x += ACCELERATION * rotationCos * deltaTime;
		playerVelocity.y += ACCELERATION * rotationSin * deltaTime;
	}
	else
	{
		playerRotation = std::fmod(playerRotation + ROTATE_SPEED * deltaTime, 360.f);
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

	/*
	if (playerPosition.x < 0) playerPosition.x = 500;
	if (playerPosition.x > 500) playerPosition.x = 0;
	if (playerPosition.y > 500) playerPosition.y = -23;
	if (playerPosition.y < -23) playerPosition.y = 500;
	*/

	if (DEBUG_PRINT_ROT) std::cout << playerRotation << std::endl;
	if (DEBUG_PRINT_POS) std::cout << playerPosition.x << ' ' << playerPosition.y << std::endl;
	if (DEBUG_PRINT_VEL) std::cout << playerVelocity.x << ' ' << playerVelocity.y << std::endl;
}

void Player::Render() 
{
	DrawTexturePro(
		playerTexture,
		(Rectangle) { 0.0f, 0.0f, (float)playerTexture.width, (float)playerTexture.height },
		(Rectangle) { playerPosition.x, playerPosition.y, (float)playerTexture.width, (float)playerTexture.height },
		(Vector2) { (float)playerTexture.width * 1 / 2, (float)playerTexture.height * 1 / 2 },
		-playerRotation + 90,
		WHITE
	);
}