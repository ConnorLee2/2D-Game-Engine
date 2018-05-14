#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>

/*
	Menu
*/


namespace GameEngine
{
	class Menu
	{
	public:
		Menu() {};
		Menu(int number, float width, float height, sf::Font font, std::string list[]);
		~Menu();

		void Draw(sf::RenderWindow &window);
		int GetPressedItem() { return selectedItemIndex; }
		void MoveUp();
		void MoveDown();

	private:
		int numberOfMenuItems;
		int selectedItemIndex;
		sf::Font font;
		sf::Text* menu;
	};
}