#include <sstream>
#include "PauseState.hpp"
#include <iostream>

#include "GameState.hpp"
#include "MainMenuState.hpp"

namespace GameEngine
{
	PauseState::PauseState(GameDataRef data) : data(data)
	{

	}

	void PauseState::Init()
	{
		// Initialise menu text
		int numberOfMenuItems = 2;
		std::string list[] = { "Main Menu", "Back"};
		menu = new Menu(numberOfMenuItems, SCREEN_WIDTH, SCREEN_HEIGHT, data->assets.GetFont("Chiaro Font"), list);

		// Initialise title text
		title.setFont(data->assets.GetFont("Chiaro Font"));
		title.setFillColor(sf::Color::White);
		title.setString("Pause Menu");
		title.setCharacterSize(50);
		title.setStyle(sf::Text::Bold);
		title.setPosition((SCREEN_WIDTH / 2) - (title.getGlobalBounds().width / 2), SCREEN_HEIGHT / (numberOfMenuItems + 1) * 0);
	}

	void PauseState::HandleInput()
	{
		sf::Event event;
		Control input;
		while (data->window.pollEvent(event))
		{
			// Checks inputs and processes them
			data->inputs.KeyboardInputs(event, data->window);
			data->inputs.ControllerInputs(event, data->window);
			input = data->inputs.popInput();
			ReactToInputDevices(input);
		}
	}

	void PauseState::Update(float dt)
	{

	}

	void PauseState::Draw(float dt)
	{
		data->window.clear(sf::Color::Black);
		data->window.draw(title);
		menu->Draw(data->window);
		data->window.display();
	}

	void PauseState::ReactToInputDevices(Control input)
	{
		if (input == Control::UP)
		{
			menu->MoveUp();
			data->audio.playSoundEffect(data->assets.GetSoundEffect("Select"));
		}
		if (input == Control::DOWN)
		{
			menu->MoveDown();
			data->audio.playSoundEffect(data->assets.GetSoundEffect("Select"));
		}
		if (input == Control::CONFIRM)
		{
			switch (menu->GetPressedItem())
			{
			case 0:
				// Switch to main menu
				data->audio.playSoundEffect(data->assets.GetSoundEffect("Confirm"));
				data->machine.RemoveState();
				data->machine.AddState(StateRef(new MainMenuState(data)), true);
			case 1:
				// Return back to game state
				data->audio.playSoundEffect(data->assets.GetSoundEffect("Cancel"));
				data->audio.setBGMVolume(100);
				data->machine.RemoveState();
			}
		}
	}
}