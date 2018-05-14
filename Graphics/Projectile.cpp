#include "Projectile.hpp"

namespace GameEngine
{
	Projectile::Projectile()
	{
	}

	Projectile::Projectile(sf::Texture texture)
	{
		moveSpeed = 3;
		direction = 0;
		damage = 10;
		lifetime = 200;
		spriteTexture = texture;
		sprite.setTexture(spriteTexture);
		//sprite.setTextureRect(sf::IntRect(0, 0, SPRITE_SIZE, SPRITE_SIZE));
	}

	Projectile::~Projectile()
	{
	}

	void Projectile::MoveProjectile(int x, int y)
	{
		sprite.move(x, y);
		//sprite.setTextureRect(intRect);
	}

	void Projectile::SetPosition(sf::Vector2f position)
	{
		sprite.setPosition(position);
	}
}