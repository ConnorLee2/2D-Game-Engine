#include "GameState.hpp"
#include "PauseState.hpp"
#include "GameWonState.hpp"
#include "GameOverState.hpp"

namespace GameEngine
{
	GameState::GameState(GameDataRef data) : data(data)
	{
		
	}

	GameState::~GameState()
	{
		delete player;
		delete enemy;
		delete projectile;
		delete popUpText;

		for (std::vector<Projectile*>::iterator it = projectileList->begin(); it != projectileList->end(); it++)
		{
			delete (*it);
		}
		projectileList->clear();
		delete projectileList;

		for (std::vector<Enemy*>::iterator it = enemyList->begin(); it != enemyList->end(); it++)
		{
			delete (*it);
		}
		enemyList->clear();
		delete enemyList;

		for (std::vector<PopUpText*>::iterator it = popUpTextList->begin(); it != popUpTextList->end(); it++)
		{
			delete (*it);
		}
		popUpTextList->clear();
		delete popUpTextList;
	}

	void GameState::Init()
	{
		// Loading in assets
		//data->assets.LoadTexture("Alm", PLAYER_SPRITE_ALM_FILEPATH);
		data->assets.LoadTexture("Robin", PLAYER_SPRITE_ROBIN_FILEPATH);
		data->assets.LoadTexture("Projectile", PROJECTILE_SPRITE_FILEPATH);
		data->assets.LoadTexture("Enemy", ENEMY_SPRITE_BONE_FILEPATH);
		data->assets.LoadFont("Chiaro Font", CHIARO_FONT);
		data->assets.LoadTexture("Tilemap", TILESET_FILEPATH);

		// File IOx	
		const int* level = data->fileIO.getLevelData();

		// Tilemap
		map.load(TILESET_FILEPATH, sf::Vector2u(32, 32), level, 16, 16);
		srand(time(NULL));

		// Get player position
		int startTile = map.getTileByType(3);
		int gridX = map.getGridX(startTile);
		int gridY = map.getGridY(startTile);

		// Set entities
		player = new Player(data->assets.GetTexture("Robin"), gridX, gridY);
		projectile = new Projectile(data->assets.GetTexture("Projectile"));
		projectileList = new std::vector<Projectile*>();
		enemyList = new std::vector<Enemy*>();
		popUpText = new PopUpText(data->assets.GetFont("Chiaro Font"));
		popUpTextList = new std::vector<PopUpText*>();

		// Generate enemies
		int numEnemy = 0;
		numEnemy = data->fileIO.getEnemyData();
		if (numEnemy == 0)
		{
			data->physics.enemiesSpawned = false;
		}
		else
		{
			data->physics.enemiesSpawned = true;
		}

		for (int i = 0; i < numEnemy; i++)
		{
			enemy = new Enemy(data->assets.GetTexture("Enemy"));

			// Set position
			int gridPos = rand() % 10;
			enemy->setGridX(gridPos);
			enemy->setGridY(gridPos);
			enemy->SetPosition(sf::Vector2f(gridPos * 32, gridPos * 32));

			// Check not spawn on bad tile
			int tileNumber = (enemy->getGridY() * 16) + enemy->getGridX();
			int tileType = map.getTile(tileNumber);
			while (tileType == 1)
			{
				gridPos = rand() % 10;
				enemy->setGridX(gridPos);
				enemy->setGridY(gridPos);
				enemy->SetPosition(sf::Vector2f(gridPos * 32, gridPos * 32));

				tileNumber = (enemy->getGridY() * 16) + enemy->getGridX();
				tileType = map.getTile(tileNumber);
			}

			// Push
			enemyList->push_back(enemy);
		}

		// Set entities
		data->entities.setPlayer(player);
		data->entities.setProjectileList(projectileList);
		data->entities.setProjectile(projectile);
		data->entities.setEnemyList(enemyList);
		data->entities.setEnemy(enemy);
		data->entities.setPopUpText(popUpText);
		data->entities.setPopUpTextList(popUpTextList);
		data->entities.setTileMap(map);
		data->physics.SetEntityManager(data->entities);

		// Load BGM
		data->audio.playBGM(BGM_LEVEL_FILEPATH);
		data->audio.loopBGM(true);
	}

	void GameState::HandleInput()
	{
		sf::Event event;
		Control input;
		while (data->window.pollEvent(event))
		{
			// Checks inputs and processes them
			data->inputs.KeyboardInputs(event, data->window);
			data->inputs.ControllerInputs(event, data->window);
			input = data->inputs.popInput();
			data->physics.ReactToInputDevices(input);
			ReactToInputDevices(input);
		}
	}

	void GameState::Update(float dt)
	{
		data->physics.Update(dt);
		data->profile.getFrameRate();
		data->profile.PrintMemoryInfo();
		if (data->physics.win)
		{
			// win state
			data->physics.win = false;
			data->machine.AddState(StateRef(new GameWonState(data)), false);

		}
		if (data->physics.lose)
		{
			// lose state
			data->physics.lose = false;
			data->machine.AddState(StateRef(new GameOverState(data)), false);
		}
	}

	void GameState::Draw(float dt)
	{
		data->window.clear(sf::Color::Black);
		data->window.draw(map);
		for (std::vector<Projectile*>::iterator it = projectileList->begin(); it != projectileList->end(); ++it)
		{
			data->window.draw((*it)->getSprite());
		}
		for (std::vector<Enemy*>::iterator it = enemyList->begin(); it != enemyList->end(); ++it)
		{
			data->window.draw((*it)->getSprite());
		}
		data->window.draw(player->getSprite());
		for (std::vector<PopUpText*>::iterator it = popUpTextList->begin(); it != popUpTextList->end(); ++it)
		{
			data->window.draw((*it)->getText());
		}
		data->window.display();
	}

	void GameState::ReactToInputDevices(Control input)
	{
		if (input == Control::START)
		{
			// Switch to pause menu
			data->audio.setBGMVolume(20);
			data->machine.AddState(StateRef(new PauseState(data)), false);
		}
	}
}