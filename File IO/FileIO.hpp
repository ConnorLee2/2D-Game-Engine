#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

/*
	Interprets data from either external data files
*/


namespace GameEngine
{
	class FileIO
	{
	public:
		FileIO();
		~FileIO();

		void loadLevelData(std::string fileName);
		int* getLevelData() { return level; }
		void loadEnemyData(std::string filename);
		int getEnemyData() { return numEnemy; }
	private:
		int level[255];
		int numEnemy;
	};
}