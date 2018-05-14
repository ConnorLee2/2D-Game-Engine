#include <sstream>
#include "MainMenuState.hpp"
#include <iostream>

#include "GameState.hpp"
#include "TutorialState.hpp"
#include "LevelChoiceState.hpp"

namespace GameEngine
{
	MainMenuState::MainMenuState(GameDataRef data) : data(data)
	{

	}

	MainMenuState::~MainMenuState()
	{
		delete menu;
	}

	void MainMenuState::Init()
	{
		// Loading in font
		data->assets.LoadFont("Chiaro Font", CHIARO_FONT);

		// Loading in sfx
		data->assets.LoadSoundEffect("Confirm", SOUND_EFFECT_CONFIRM_FILEPATH);
		data->assets.LoadSoundEffect("Cancel", SOUND_EFFECT_CANCEL_FILEPATH);
		data->assets.LoadSoundEffect("Select", SOUND_EFFECT_SELECT_FILEPATH);

		// Initialise menu text
		int numberOfMenuItems = 3;
		std::string list[] = {"Start", "Demo", "Exit"};
		menu = new Menu(numberOfMenuItems, SCREEN_WIDTH, SCREEN_HEIGHT, data->assets.GetFont("Chiaro Font"), list);

		// Initialise title text
		title.setFont(data->assets.GetFont("Chiaro Font"));
		title.setFillColor(sf::Color::White);
		title.setString("Game");
		title.setCharacterSize(50);
		title.setStyle(sf::Text::Bold);
		title.setPosition((SCREEN_WIDTH / 2) - (title.getGlobalBounds().width / 2), SCREEN_HEIGHT / (numberOfMenuItems + 1) * 0);

		// Load BGM
		data->audio.playBGM(BGM_MAIN_MENU_FILEPATH);
		data->audio.loopBGM(true);
	}

	void MainMenuState::HandleInput()
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

	void MainMenuState::Update(float dt)
	{
	}

	void MainMenuState::Draw(float dt)
	{
		data->window.clear(sf::Color::Black);
		data->window.draw(title);
		menu->Draw(data->window);
		data->window.display();
	}

	void MainMenuState::ReactToInputDevices(Control input)
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
				// Game state
				data->audio.playSoundEffect(data->assets.GetSoundEffect("Confirm"));
				data->machine.AddState(StateRef(new LevelChoiceState(data)), false);
				break;
			case 1:
				// Tutorial state
				data->audio.playSoundEffect(data->assets.GetSoundEffect("Confirm"));
				// disabled, should be called demo
				//data->machine.AddState(StateRef(new TutorialState(data)), true);
				break;
			case 2:
				// Shutdown
				data->window.close();
				break;
			}
		}
	}
}