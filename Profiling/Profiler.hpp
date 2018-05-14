#pragma once
#include <SFML\System.hpp>
#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <psapi.h>

/*
	Provides information regarding performance of the game.
*/


namespace GameEngine
{
	class Profiler
	{
	public:
		Profiler();
		~Profiler();

		void getFrameRate();
		void PrintMemoryInfo();
	private:
		sf::Clock clock;
		sf::Time time;
	};
}