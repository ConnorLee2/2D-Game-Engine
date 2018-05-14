#include "EntityManager.hpp"

namespace GameEngine
{
	EntityManager::EntityManager()
	{
	}


	EntityManager::~EntityManager()
	{
		delete player;
		delete projectile;
		delete enemy;
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
}