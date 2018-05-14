#pragma once
#include "Game.hpp"
#include "Menu.hpp"

/*
	Level choice state
*/


namespace GameEngine
{
	class LevelChoiceState : public State
	{
	public:
		LevelChoiceState(GameDataRef data);
		~LevelChoiceState();
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