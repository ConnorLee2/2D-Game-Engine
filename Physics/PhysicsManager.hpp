#pragma once
#include "InputManager.hpp"
#include "EntityManager.hpp"
#include <iostream>
#include <vector>

/*
	Manages movement and collision detections
*/


namespace GameEngine
{
	class PhysicsManager
	{
	public:
		PhysicsManager();
		~PhysicsManager();

		void SetEntityManager(EntityManager& entities) { this->entities = entities; }
		void Update(float dt);
		void ReactToInputDevices(Control input);
		void AcidDamage();
		void MoveUp();
		void MoveDown();
		void MoveLeft();
		void MoveRight();

		bool win;
		bool lose;
		bool enemiesSpawned;
	private:
		std::vector<Projectile*>* projectileList;
		std::vector<Enemy*>* enemyList;
		std::vector<PopUpText*>* popUpTextList;
		EntityManager entities;
		Player* player;
		Projectile* projectile;
		PopUpText* popUpText;
		TileMap map;
		sf::Clock clock;
		sf::Time elapsed;
		bool canFire;
		int animationCounter;
		int walkingCounter;
	};
}