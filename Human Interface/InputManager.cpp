#include "InputManager.hpp"

namespace GameEngine
{
	void InputManager::KeyboardInputs(sf::Event event, sf::RenderWindow &window)
	{
		// Close window if window cross is clicked
		if (event.type == sf::Event::Closed)
		{
			window.close();
		}

		// Keyboard controls
		if (event.type == sf::Event::KeyPressed)
		{
			switch (event.key.code)
			{
			case sf::Keyboard::W:
				addEvent(Control::UP);
				break;
			case sf::Keyboard::A:
				addEvent(Control::LEFT);
				break;
			case sf::Keyboard::S:
				addEvent(Control::DOWN);
				break;
			case sf::Keyboard::D:
				addEvent(Control::RIGHT);
				break;
			case sf::Keyboard::Escape:
				addEvent(Control::START);
				break;
			case sf::Keyboard::O:
				addEvent(Control::CONFIRM);
				break;
			case sf::Keyboard::P:
				addEvent(Control::CANCEL);
				break;
			}
		}
	}

	void InputManager::ControllerInputs(sf::Event event, sf::RenderWindow & window)
	{
		// Controller controls
		if (event.type == sf::Event::JoystickMoved || event.type == sf::Event::JoystickButtonPressed)
		{
			// Get Controller ID
			int controllerID = event.joystickMove.joystickId;

			// WASD
			float x = sf::Joystick::getAxisPosition(controllerID, sf::Joystick::PovX);
			float y = sf::Joystick::getAxisPosition(controllerID, sf::Joystick::PovY);

			if (y >= 70 && y <= 100)
			{
				addEvent(Control::UP);
			}
			if (y <= -70 && y >= -100)
			{
				addEvent(Control::DOWN);
			}
			if (x <= -70 && x >= -100)
			{
				addEvent(Control::LEFT);
			}
			if (x >= 70 && x <= 100)
			{
				addEvent(Control::RIGHT);
			}

			// Start, A, B
			if (event.type == sf::Event::JoystickButtonPressed)
			{
				if (sf::Joystick::isButtonPressed(controllerID, CONTROLLER_BUTTON_MENU))
				{
					addEvent(Control::START);
				}
				if (sf::Joystick::isButtonPressed(controllerID, CONTROLLER_BUTTON_A))
				{
					addEvent(Control::CONFIRM);
				}
				if (sf::Joystick::isButtonPressed(controllerID, CONTROLLER_BUTTON_B))
				{
					addEvent(Control::CANCEL);
				}
			}
		}
	}

	void InputManager::addEvent(Control input)
	{
		inputList.push_back(input);
	}

	Control InputManager::popInput()
	{
		// No inputs in list
		if (inputList.size() == 0)
		{
			return Control::EMPTY;
		}
		// List not empty
		else
		{
			Control input = inputList.front();
			inputList.pop_front();
			return input;
		}
	}

	void InputManager::CleanUp()
	{
		inputList.clear();
	}
}