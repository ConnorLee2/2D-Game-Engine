#pragma once
#include <SFML\Graphics.hpp>

/*
	Projectile class
*/
#define SPRITE_SIZE 32


namespace GameEngine
{
	class Projectile
	{
	public:
		Projectile();
		Projectile(sf::Texture texture);
		~Projectile();

		void MoveProjectile(int x, int y);

		int getMoveSpeed() { return moveSpeed; }
		sf::Sprite getSprite() { return sprite; }
		sf::Texture getSpriteTexture() { return spriteTexture; }
		void SetPosition(sf::Vector2f position);

		int getDirection() { return direction; }
		void setDirection(int direction) { this->direction = direction; }

		int getDamage() { return damage; }
		void setDamage(int damage) { this->damage = damage; }

		int getLifetime() { return lifetime; }
		void setLifetime(int lifetime) { this->lifetime = lifetime; }
	private:
		sf::Sprite sprite;
		sf::Texture spriteTexture;

		int damage;
		int moveSpeed;
		int direction;
		int lifetime;
	};
}