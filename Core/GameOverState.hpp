#pragma once
#include "Game.hpp"
#include "Menu.hpp"

/*
	Game over screen
*/


namespace GameEngine
{
	class GameOverState : public State
	{
	public:
		GameOverState(GameDataRef data);

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