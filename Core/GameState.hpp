#pragma once
#include "Game.hpp"
#include <vector>

/*
	Game screen
*/


namespace GameEngine
{
	class GameState : public State
	{
	public:
		GameState(GameDataRef data);
		~GameState();

		void Init();

		void HandleInput();
		void Update(float dt);
		void Draw(float dt);

		void ReactToInputDevices(Control input);
	private:

		GameDataRef data;

		Player* player;
		Enemy* enemy;
		Projectile* projectile;
		PopUpText* popUpText;
		TileMap map;
		std::vector<Projectile*>* projectileList;
		std::vector<Enemy*>* enemyList;
		std::vector<PopUpText*>* popUpTextList;
	};
}