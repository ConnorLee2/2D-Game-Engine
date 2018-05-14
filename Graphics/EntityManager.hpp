#pragma once
#include "Player.hpp"
#include "Projectile.hpp"
#include "Enemy.hpp"
#include "PopUpText.hpp"
#include "TileMap.hpp"
#include <vector>

/*
	Stores a list of entities
*/


namespace GameEngine
{
	class EntityManager
	{
	public:
		EntityManager();
		~EntityManager();

		void setPlayer(Player* player) { this->player = player; }
		Player* getPlayer() { return player; }

		void setProjectileList(std::vector<Projectile*>* projectileList) { this->projectileList = projectileList; }
		std::vector<Projectile*>* getprojectileList() { return projectileList; }

		void setProjectile(Projectile* projectile) { this->projectile = projectile; }
		Projectile* getProjectile() { return projectile; }

		void setEnemyList(std::vector<Enemy*>* enemyList) { this->enemyList = enemyList; }
		std::vector<Enemy*>* getEnemyList() { return enemyList; }

		void setEnemy(Enemy* enemy) { this->enemy = enemy; }
		Enemy* getEnemy() { return enemy; }

		void setPopUpTextList(std::vector<PopUpText*>* popUpTextList) { this->popUpTextList = popUpTextList; }
		std::vector<PopUpText*>* getPopUpTextList() { return popUpTextList; }

		void setPopUpText(PopUpText* popUpText) { this->popUpText = popUpText; }
		PopUpText* getPopUpText() { return popUpText; }

		void setTileMap(TileMap map) { this->map = map; }
		TileMap getTileMap() { return map; }

	private:
		std::vector<Projectile*>* projectileList;
		std::vector<Enemy*>* enemyList;
		std::vector<PopUpText*>* popUpTextList;
		TileMap map;
		Player* player;
		Projectile* projectile;
		Enemy* enemy;
		PopUpText* popUpText;
	};
}