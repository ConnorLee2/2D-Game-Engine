#pragma once
#include "Game.hpp"
#include "Menu.hpp"

/*
	Game won screen
*/


namespace GameEngine
{
	class GameWonState : public State
	{
	public:
		GameWonState(GameDataRef data);

		void Init();

		void HandleInput();
		void Update(float dt);
		void Draw(float dt);

		void ReactToInputDevices(Control input);
	private:
		GameDataRef data;
		Menu* menu;
		sf::Text title;
	};
}