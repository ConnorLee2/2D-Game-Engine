#include "Enemy.hpp"

namespace GameEngine
{
	Enemy::Enemy(sf::Texture texture)
	{
		moveSpeed = 1;
		hp = 50;
		damage = 10;
		move = true;
		direction = rand() % 6;
		spriteTexture = texture;
		sprite.setTexture(spriteTexture);
		sprite.setTextureRect(sf::IntRect(0, 0, SPRITE_SIZE, SPRITE_SIZE));
	}


	Enemy::~Enemy()
	{
	}

	void Enemy::MoveEnemy(int x, int y, sf::IntRect intRect)
	{
		sprite.move(x, y);
		sprite.setTextureRect(intRect);
	}
}