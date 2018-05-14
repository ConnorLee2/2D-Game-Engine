#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>
#include <list>
#include "Controller Definitions.hpp"

/*
	Handles user inputs, permits the user to interact with the game
*/


namespace GameEngine
{
	enum Control
	{
		UP, DOWN, LEFT, RIGHT, CONFIRM, CANCEL, START, EMPTY
	};

	class InputManager
	{
	public:
		InputManager() {}
		~InputManager() {}

		void KeyboardInputs(sf::Event event, sf::RenderWindow &window);
		void ControllerInputs(sf::Event event, sf::RenderWindow &window);

		void addEvent(Control input);
		Control popInput();

		void CleanUp();
	private:
		std::list<Control> inputList;
	};
}