#pragma once
#include "Game.hpp"
#include "Menu.hpp"

/*
	Main Menu screen
*/


namespace GameEngine
{
	class MainMenuState : public State
	{
	public:
		MainMenuState(GameDataRef data);
		~MainMenuState();
		void Init();

		void HandleInput();
		void Update(float dt);
		void Draw(float dt);
		void ReactToInputDevices(Control input);
	private:
		GameDataRef data;

		sf::Clock clock;
		Menu* menu;
		sf::Text title;
	};
}