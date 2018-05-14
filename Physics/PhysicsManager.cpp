#include "PhysicsManager.hpp"

namespace GameEngine
{
	PhysicsManager::PhysicsManager()
	{
		animationCounter = 0;
		win = false;
		lose = false;
		canFire = true;
	}

	PhysicsManager::~PhysicsManager()
	{
		delete player;
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

	void PhysicsManager::Update(float dt)
	{
		elapsed = clock.getElapsedTime();
		srand(time(NULL));

		// Set entities
		projectileList = entities.getprojectileList();
		enemyList = entities.getEnemyList();
		popUpTextList = entities.getPopUpTextList();
		player = entities.getPlayer();
		popUpText = new PopUpText(entities.getPopUpText()->getFont());
		map = entities.getTileMap();
		int tileNumber = 0;
		int tileType = 0;

		// Animation animationCounter
		animationCounter++;
		if (animationCounter >= 4)
		{
			animationCounter = 0;
		}

		// Collision detection (player and enemy)
		if (elapsed.asSeconds() >= 0.2)
		{
			clock.restart();
			// Only enter after not taking damage for 0.2 seconds
			for (std::vector<Enemy*>::iterator it = enemyList->begin(); it != enemyList->end(); ++it)
			{
				if (player->getSprite().getGlobalBounds().intersects((*it)->getSprite().getGlobalBounds()))
				{
					// Collision found
					std::cout << player << " collision with " << (*it) << std::endl;

					// Set damage
					int damage = (*it)->getDamage();
					popUpText->setString(std::to_string(damage));
					popUpText->setColour(sf::Color::Red);
					popUpText->setPosition(player->getSprite().getPosition());
					entities.getPopUpTextList()->push_back(popUpText);

					// HP calculation and set
					std::cout << "Current HP: " << player->getHP() << std::endl;
					int newHP = player->getHP() - (*it)->getDamage();
					player->setHP(newHP);
					std::cout << "Current HP: " << player->getHP() << std::endl;

					// Player dead?
					if (player->getHP() <= 0)
					{
						std::cout << "Player dead" << std::endl;
					}
				}
			}
		}

		// Collision detection (projectile and enemy)
		for (std::vector<Projectile*>::iterator proj = projectileList->begin(); proj != projectileList->end(); ++proj)
		{
			bool result = false;
			for (std::vector<Enemy*>::iterator it = enemyList->begin(); it != enemyList->end(); ++it)
			{
				// Check collision
				if ((*proj)->getSprite().getGlobalBounds().intersects((*it)->getSprite().getGlobalBounds()))
				{
					// Colision detected
					std::cout << (*it) << " collision with " << (*proj) << std::endl;

					// Set damage
					int damage = (*it)->getDamage();
					popUpText->setString(std::to_string(damage));
					popUpText->setColour(sf::Color::Yellow);
					popUpText->setPosition((*it)->getSprite().getPosition());
					entities.getPopUpTextList()->push_back(popUpText);

					// Damage calculation and set
					std::cout << "Current HP: " << (*it)->getHP() << std::endl;
					int newHP = (*it)->getHP() - (*proj)->getDamage();
					(*it)->setHP(newHP);
					std::cout << "Current HP: " << (*it)->getHP() << std::endl;

					// Enemy dead?
					if ((*it)->getHP() <= 0)
					{
						delete (*it);
						it = enemyList->erase(it);
						result = true;
						break;
					}
					// Exit after collision
					else
					{
						result = true;
						break;
					}
				}
			}

			// Delete projectile if collision is detected
			if (result)
			{
				delete (*proj);
				proj = projectileList->erase(proj);
				break;
			}
		}

		// Projectile firerate
		if (!canFire)
		{
			if (elapsed.asSeconds() >= 0.2)
			{
				clock.restart();
				canFire = true;
			}
		}

		// Projectile lifetime
		for (std::vector<Projectile*>::iterator proj = projectileList->begin(); proj != projectileList->end(); ++proj)
		{
			if ((*proj)->getLifetime() <= 0)
			{
				delete (*proj);
				proj = projectileList->erase(proj);
				break;
			}
			else
			{
				int newLifetime = (*proj)->getLifetime() - 10;
				(*proj)->setLifetime(newLifetime);
			}
		}

		// Move projectiles
		for (std::vector<Projectile*>::iterator it = projectileList->begin(); it != projectileList->end(); ++it)
		{
			switch ((*it)->getDirection())
			{
			case Control::UP:
				(*it)->MoveProjectile(0, -(*it)->getMoveSpeed());
				break;
			case Control::DOWN:
				(*it)->MoveProjectile(0, (*it)->getMoveSpeed());
				break;
			case Control::LEFT:
				(*it)->MoveProjectile(-(*it)->getMoveSpeed(), 0);
				break;
			case Control::RIGHT:
				(*it)->MoveProjectile((*it)->getMoveSpeed(), 0);
				break;
			}
		}

		// Move popUpText
		for (std::vector<PopUpText*>::iterator text = popUpTextList->begin(); text != popUpTextList->end(); ++text)
		{
			(*text)->MovePopUpText(0, -(*text)->getMoveSpeed());
		}

		// popUpText lifetime
		for (std::vector<PopUpText*>::iterator text = popUpTextList->begin(); text != popUpTextList->end(); ++text)
		{
			if ((*text)->getLifetime() <= 0)
			{
				//delete (*text);
				//text = popUpTextList->erase(text);
				break;
			}
			else
			{
				int newLifetime = (*text)->getLifetime() - 5;
				(*text)->setLifetime(newLifetime);
			}
		}

		// Wall collision and enemy
		/*
		for (std::vector<Enemy*>::iterator it = enemyList->begin(); it != enemyList->end(); ++it)
		{
			tileNumber = ((*it)->getGridY() * 16) + (*it)->getGridX();
			tileType = map.getTile(tileNumber);
			if (tileType == 1)
			{
				std::cout << (*it) << "Enemy on the wrong tile" << std::endl;
				//(*it)->setMove(false);
				// do something
				// grid positions arent being set correctly?
			}
		}
		*/

		// Move enemies
		for (std::vector<Enemy*>::iterator it = enemyList->begin(); it != enemyList->end(); ++it)
		{
			if ((*it)->getMove())
			{
				float x = (*it)->getSprite().getGlobalBounds().top;
				float y = (*it)->getSprite().getGlobalBounds().left;
				switch ((*it)->getDirection())
				{
				case 0:
					if (x + (*it)->getMoveSpeed() < 32)
					{
						// dont move
					}
					else
					{
						(*it)->MoveEnemy(0, -(*it)->getMoveSpeed(), sf::IntRect(animationCounter * 32, 3 * 32, 32, 32));
						(*it)->setGridY((*it)->getGridY() - 1);
					}
					break;
				case 1:
					if (x + (*it)->getMoveSpeed() > 448)
					{
						// dont move
					}
					else
					{
						(*it)->MoveEnemy(0, (*it)->getMoveSpeed(), sf::IntRect(animationCounter * 32, 2 * 32, 32, 32));
						(*it)->setGridY((*it)->getGridY() + 1);
					}
					break;
				case 2:
					if (y + (*it)->getMoveSpeed() < 32)
					{
						// dont move
					}
					else
					{
						(*it)->MoveEnemy(-(*it)->getMoveSpeed(), 0, sf::IntRect(animationCounter * 32, 0 * 32, 32, 32));
						(*it)->setGridX((*it)->getGridX() - 1);
					}
					break;
				case 3:
					if (y + (*it)->getMoveSpeed() > 448)
					{
						// dont move
					}
					else
					{
						(*it)->MoveEnemy((*it)->getMoveSpeed(), 0, sf::IntRect(animationCounter * 32, 1 * 32, 32, 32));
						(*it)->setGridX((*it)->getGridX() + 1);
					}
					break;
				default:
					// do nothing (pause)
					break;
				}
			}
		}

		// Walk in a direction for a set time?
		walkingCounter++;
		if (walkingCounter >= 100)
		{
			walkingCounter = 0;
			// randomise direction
			for (std::vector<Enemy*>::iterator it = enemyList->begin(); it != enemyList->end(); ++it)
			{
				(*it)->setDirection(rand() % 8);
			}
		}

		// Check number of enemies
		if (enemyList->size() <= 0 && enemiesSpawned)
		{
			win = true;
		}

		// Check player HP
		if (player->getHP() <= 0)
		{
			lose = true;
		}
	}

	void PhysicsManager::AcidDamage()
	{
		int damage = 5;

		// HP calculation and set
		std::cout << "Current HP: " << player->getHP() << std::endl;
		int newHP = player->getHP() - damage;
		player->setHP(newHP);
		std::cout << "Current HP: " << player->getHP() << std::endl;

		// Pop up text
		popUpText->setString(std::to_string(damage));
		popUpText->setColour(sf::Color::Red);
		popUpText->setPosition(player->getSprite().getPosition());
		entities.getPopUpTextList()->push_back(popUpText);
	}

	void PhysicsManager::MoveUp()
	{
		player->MovePlayer(0, -player->getMoveSpeed(), sf::IntRect(animationCounter * 32, 3 * 32, 32, 32));
		player->setDirection(Control::UP);
		player->setGridY(player->getGridY() - 1);
	}

	void PhysicsManager::MoveDown()
	{
		player->MovePlayer(0, player->getMoveSpeed(), sf::IntRect(animationCounter * 32, 2 * 32, 32, 32));
		player->setDirection(Control::DOWN);
		player->setGridY(player->getGridY() + 1);
	}

	void PhysicsManager::MoveLeft()
	{
		player->MovePlayer(-player->getMoveSpeed(), 0, sf::IntRect(animationCounter * 32, 0, 32, 32));
		player->setDirection(Control::LEFT);
		player->setGridX(player->getGridX() - 1);
	}

	void PhysicsManager::MoveRight()
	{
		player->MovePlayer(player->getMoveSpeed(), 0, sf::IntRect(animationCounter * 32, 1 * 32, 32, 32));
		player->setDirection(Control::RIGHT);
		player->setGridX(player->getGridX() + 1);
	}

	void PhysicsManager::ReactToInputDevices(Control input)
	{
		// Get entities
		player = entities.getPlayer();
		projectileList = entities.getprojectileList();
		projectile = new Projectile(entities.getProjectile()->getSpriteTexture());
		map = entities.getTileMap();

		// Set up projectiles
		projectile->SetPosition(player->getSprite().getPosition());
		projectile->setDirection(player->getDirection());

		int tileNumber = 0;
		int tileType = 0;

		// Player movement and collision
		if (input == Control::UP)
		{
			tileNumber = ((player->getGridY() - 1) * 16) + player->getGridX();
			tileType = map.getTile(tileNumber);

			// Collision Detection
			if (tileType == 1)
			{
				player->MovePlayer(0, 0, sf::IntRect(animationCounter * 32, 3 * 32, 32, 32));
				player->setDirection(Control::UP);
			}
			// Win condition
			else if (tileType == 2)
			{
				MoveUp();
				win = true;
			}
			// Acid tiles
			else if (tileType == 4)
			{
				MoveUp();
				AcidDamage();
			}
			else
			{
				MoveUp();
			}
		}
		if (input == Control::DOWN)
		{
			tileNumber = ((player->getGridY() + 1) * 16) + player->getGridX();
			tileType = map.getTile(tileNumber);

			// Collision Detection
			if (tileType == 1)
			{
				player->MovePlayer(0, 0, sf::IntRect(animationCounter * 32, 2 * 32, 32, 32));
				player->setDirection(Control::DOWN);
			}
			// Win condition
			else if (tileType == 2)
			{
				MoveDown();
				win = true;
			}
			// Acid tiles
			else if (tileType == 4)
			{
				MoveDown();
				AcidDamage();
			}
			else if (tileType == 0)
			{
				MoveDown();
			}
			else
			{
				MoveDown();
				// dont move
			}
		}
		if (input == Control::LEFT)
		{
			tileNumber = (player->getGridY() * 16) + (player->getGridX() - 1);
			tileType = map.getTile(tileNumber);

			// Collision Detection
			if (tileType == 1)
			{
				player->MovePlayer(0, 0, sf::IntRect(animationCounter * 32, 0, 32, 32));
				player->setDirection(Control::LEFT);
			}
			// Win condition
			else if (tileType == 2)
			{
				MoveLeft();
				win = true;
			}
			// Acid tiles
			else if (tileType == 4)
			{
				MoveLeft();
				AcidDamage();
			}
			else
			{
				MoveLeft();
			}
		}
		if (input == Control::RIGHT)
		{
			tileNumber = (player->getGridY() * 16) + (player->getGridX() + 1);
			tileType = map.getTile(tileNumber);

			// Collision Detection
			if (tileType == 1)
			{
				player->MovePlayer(0, 0, sf::IntRect(animationCounter * 32, 1 * 32, 32, 32));
				player->setDirection(Control::RIGHT);
			}
			// Win condition
			else if (tileType == 2)
			{
				MoveRight();
				win = true;
			}
			// Acid tile
			else if (tileType == 4)
			{
				MoveRight();
				AcidDamage();
			}
			else
			{
				MoveRight();
			}
		}
		if (canFire)
		{
			if (input == Control::CONFIRM)
			{
				entities.getprojectileList()->push_back(projectile);
				canFire = false;
			}
		}
	}
}