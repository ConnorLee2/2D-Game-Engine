#include "PopUpText.hpp"

namespace GameEngine
{
	PopUpText::PopUpText()
	{
	}

	PopUpText::PopUpText(sf::Font font)
	{
		textFont = font;
		text.setFont(textFont);
		text.setCharacterSize(15);
		text.setFillColor(sf::Color::White);
		lifetime = 100;
		moveSpeed = 2;
	}


	PopUpText::~PopUpText()
	{
	}

	void PopUpText::MovePopUpText(int x, int y)
	{
		text.move(x, y);
	}
}