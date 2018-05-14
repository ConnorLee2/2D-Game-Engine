#pragma once
#include "Game.hpp"
#include <vector>

/*
	Tutorial state
*/


namespace GameEngine 
{
	class TutorialState : public State
	{
	public:
		TutorialState();
		TutorialState(GameDataRef data);
		~TutorialState();
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