#include "Game.hpp"
#include "MainMenuState.hpp"

namespace GameEngine
{
	Game::Game(int width, int height, std::string title)
	{
		data->window.create(sf::VideoMode(width, height), title, sf::Style::Close | sf::Style::Titlebar);
		data->window.setFramerateLimit(60);
		data->machine.AddState(StateRef(new MainMenuState(data)));
		Run();
	}

	void Game::Run()
	{
		float newTime, frameTime, interpolation;

		float currentTime = clock.getElapsedTime().asSeconds();
		float accumulator = 0.0f;

		// Game Loop
		while (data->window.isOpen()) 
		{
			// Process state changes
			data->machine.ProcessStateChanges();

			// Time
			newTime = clock.getElapsedTime().asSeconds();
			frameTime = newTime - currentTime;

			if (frameTime > 0.25f)
			{
				frameTime = 0.25f;
			}

			currentTime = newTime;
			accumulator += frameTime;

			// Handling input and physics
			while (accumulator >= dt)
			{
				data->machine.GetActiveState()->HandleInput();
				data->machine.GetActiveState()->Update(dt);

				accumulator -= dt;
			}

			// Drawing
			interpolation = accumulator / dt;
			data->machine.GetActiveState()->Draw(interpolation);
		}

		// Shutdown
		if (data->window.isOpen() != true)
		{
			data->assets.CleanUp();
			data->machine.CleanUp();
			data->inputs.CleanUp();
		}
	}
}