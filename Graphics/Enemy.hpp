#pragma once
#include <SFML\Graphics.hpp>

/*
	Enemy class
*/
#define SPRITE_SIZE 32


namespace GameEngine
{
	class Enemy
	{
	public:
		Enemy() {};
		Enemy(sf::Texture texture);
		~Enemy();

		void MoveEnemy(int x, int y, sf::IntRect intRect);

		int getMoveSpeed() { return moveSpeed; }
		sf::Sprite getSprite() { return sprite; }

		void SetPosition(sf::Vector2f position) { sprite.setPosition(position); }

		int getDirection() { return direction; }
		void setDirection(int direction) { this->direction = direction; }

		int getHP() { return hp; }
		void setHP(int hp) { this->hp = hp; }

		int getDamage() { return damage; }
		void setDamage(int damage) { this->damage = damage; }

		int getGridX() { return gridX; }
		void setGridX(int gridX) { this->gridX = gridX; }

		int getGridY() { return gridY; }
		void setGridY(int gridY) { this->gridY = gridY; }

		void setMove(bool move) { this->move = move; }
		bool getMove() { return move; }
	private:
		sf::Sprite sprite;
		sf::Texture spriteTexture;

		int moveSpeed;
		int direction;
		int hp;
		int damage;
		int gridX;
		int gridY;
		bool move;
	};
}