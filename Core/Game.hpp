#pragma once
#include <memory>
#include <string>
#include <SFML\Graphics.hpp>
#include "StateMachine.hpp"
#include "Definitions.hpp"
#include "AssetManager.hpp"
#include "InputManager.hpp"
#include "AudioManager.hpp"
#include "EntityManager.hpp"
#include "PhysicsManager.hpp"
#include "FileIO.hpp"
#include "Profiler.hpp"


namespace GameEngine
{
	// Contains all the subsystems
	struct GameData
	{
		StateMachine machine;
		sf::RenderWindow window;
		AssetManager assets;
		InputManager inputs;
		AudioManager audio;
		EntityManager entities;
		PhysicsManager physics;
		FileIO fileIO;
		Profiler profile;
	};

	typedef std::shared_ptr<GameData> GameDataRef;

	class Game
	{
	public:
		Game(int width, int height, std::string title);
		~Game() {};

	private:
		const float dt = 1.0f / 60.0f;
		sf::Clock clock;

		GameDataRef data = std::make_shared<GameData>();

		void Run();
	};
}