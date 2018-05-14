#include "FileIO.hpp"

namespace GameEngine
{
	FileIO::FileIO()
	{
		numEnemy = 0;
	}

	FileIO::~FileIO()
	{
	}

	void FileIO::loadLevelData(std::string fileName)
	{
		// Textfile must be a list of strings
		int n = 0;
		std::ifstream file(fileName);
		while (file.good())
		{
			char c = file.get();
			//std::cout << c;
			int a = c - 48;
			level[n] = a;
			n++;
		}
		file.close();
		/*
		std::cout << std::endl;
		for (int i = 0; i < 256; i++)
		{
			std::cout << level[i];
		}
		*/
	}
	void FileIO::loadEnemyData(std::string fileName)
	{
		std::ifstream file(fileName);
		std::string line;
		while (std::getline(file, line))
		{
			//std::istringstream iss(line);
			numEnemy = std::stoi(line);
		}
		file.close();
	}
}