#pragma once
#include <SFML\Graphics.hpp>

/*
	Player class
*/
#define SPRITE_SIZE 32


namespace GameEngine
{
	class Player
	{
	public:
		Player() {};
		Player(sf::Texture texture, int x, int y);
		~Player();

		void MovePlayer(int x, int y, sf::IntRect intRect);

		int getMoveSpeed() { return moveSpeed; }
		sf::Sprite getSprite() { return sprite; }

		int getDirection() { return direction; }
		void setDirection(int direction) { this->direction = direction; }

		int getHP() { return hp; }
		void setHP(int hp) { this->hp = hp; }

		int getGridX() { return gridX; }
		void setGridX(int gridX) { this->gridX = gridX; }

		int getGridY() { return gridY; }
		void setGridY(int gridY) { this->gridY = gridY; }
	private:
		sf::Sprite sprite;
		sf::Texture spriteTexture;

		int moveSpeed;
		int direction;
		int hp;
		int gridX;
		int gridY;
	};
}