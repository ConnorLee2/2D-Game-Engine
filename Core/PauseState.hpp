#pragma once
#include "Game.hpp"
#include "Menu.hpp"

/*
	Pause screen
*/


namespace GameEngine
{
	class PauseState : public State
	{
	public:
		PauseState(GameDataRef data);

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