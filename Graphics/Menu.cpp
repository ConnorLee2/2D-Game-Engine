#include "Menu.hpp"

namespace GameEngine
{
	Menu::Menu(int number, float width, float height, sf::Font font, std::string list[])
	{
		// Set up menu variables
		numberOfMenuItems = number;
		menu = new sf::Text[numberOfMenuItems];
		this->font = font;

		// Initialise menu
		for (int i = 0; i < numberOfMenuItems; i++)
		{
			menu[i].setFont(this->font);
			menu[i].setFillColor(sf::Color::White);
			menu[i].setString(list[i]);
			menu[i].setPosition((width / 2) - (menu[i].getGlobalBounds().width / 2), height / (numberOfMenuItems + 1) * (i + 1));
		}

		// Set default menu item
		selectedItemIndex = 0;
		menu[selectedItemIndex].setFillColor(sf::Color::Green);
	}

	Menu::~Menu()
	{
		delete[] menu;
	}

	void Menu::Draw(sf::RenderWindow &window)
	{
		for (int i = 0; i < numberOfMenuItems; i++)
		{
			window.draw(menu[i]);
		}
	}

	void Menu::MoveUp()
	{
		if (selectedItemIndex - 1 >= 0)
		{
			menu[selectedItemIndex].setFillColor(sf::Color::White);
			selectedItemIndex--;
			menu[selectedItemIndex].setFillColor(sf::Color::Green);
		}
	}

	void Menu::MoveDown()
	{
		if (selectedItemIndex + 1 < numberOfMenuItems)
		{
			menu[selectedItemIndex].setFillColor(sf::Color::White);
			selectedItemIndex++;
			menu[selectedItemIndex].setFillColor(sf::Color::Green);
		}
	}
}