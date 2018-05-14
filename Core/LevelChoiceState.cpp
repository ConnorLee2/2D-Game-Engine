#include <sstream>
#include "LevelChoiceState.hpp"
#include <iostream>

#include "GameState.hpp"
#include "TutorialState.hpp"

namespace GameEngine
{
	LevelChoiceState::LevelChoiceState(GameDataRef data) : data(data)
	{

	}

	LevelChoiceState::~LevelChoiceState()
	{
		delete menu;
	}

	void LevelChoiceState::Init()
	{
		// Initialise menu text
		int numberOfMenuItems = 3;
		std::string list[] = { "Level One", "Level Two", "Back" };
		menu = new Menu(numberOfMenuItems, SCREEN_WIDTH, SCREEN_HEIGHT, data->assets.GetFont("Chiaro Font"), list);

		// Initialise title text
		title.setFont(data->assets.GetFont("Chiaro Font"));
		title.setFillColor(sf::Color::White);
		title.setString("Level Selection");
		title.setCharacterSize(50);
		title.setStyle(sf::Text::Bold);
		title.setPosition((SCREEN_WIDTH / 2) - (title.getGlobalBounds().width / 2), SCREEN_HEIGHT / (numberOfMenuItems + 1) * 0);
	}

	void LevelChoiceState::HandleInput()
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

	void LevelChoiceState::Update(float dt)
	{
	}

	void LevelChoiceState::Draw(float dt)
	{
		data->window.clear(sf::Color::Black);
		data->window.draw(title);
		menu->Draw(data->window);
		data->window.display();
	}

	void LevelChoiceState::ReactToInputDevices(Control input)
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
				// Level one state
				data->audio.playSoundEffect(data->assets.GetSoundEffect("Confirm"));
				// Set level data
				data->fileIO.loadLevelData(LEVEL_ONE_FILEPATH);
				data->fileIO.loadEnemyData(LEVEL_ONE_ENEMY_DATA_FILEPATH);
				data->machine.AddState(StateRef(new GameState(data)), true);
				
				break;
			case 1:
				// Level two state
				data->audio.playSoundEffect(data->assets.GetSoundEffect("Confirm"));
				// Set level data
				data->fileIO.loadLevelData(LEVEL_TWO_FILEPATH);
				data->fileIO.loadEnemyData(LEVEL_TWO_ENEMY_DATA_FILEPATH);
				data->machine.AddState(StateRef(new GameState(data)), true);
				break;
			case 2:
				// Back
				data->audio.playSoundEffect(data->assets.GetSoundEffect("Cancel"));
				data->machine.RemoveState();
				break;
			}
		}
	}
}