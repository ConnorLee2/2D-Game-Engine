#include "Player.hpp"

namespace GameEngine
{
	Player::Player(sf::Texture texture, int x, int y)
	{
		moveSpeed = 32;
		direction = 0;
		hp = 50;
		gridX = x;
		gridY = y;
		spriteTexture = texture;
		sprite.setTexture(spriteTexture);
		sprite.setTextureRect(sf::IntRect(0, 0, SPRITE_SIZE, SPRITE_SIZE));
		sprite.setPosition(gridX * 32, gridY * 32);
	}


	Player::~Player()
	{
	}

	void Player::MovePlayer(int x, int y, sf::IntRect intRect)
	{
		sprite.move(x, y);
		sprite.setTextureRect(intRect);
	}
}