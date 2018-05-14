#pragma once
#include <SFML\Graphics.hpp>

/*
	Pop-up text class
*/


namespace GameEngine
{
	class PopUpText
	{
	public:
		PopUpText();
		PopUpText(sf::Font font);
		~PopUpText();

		void MovePopUpText(int x, int y);

		sf::Text getText() { return text; }
		sf::Font getFont() { return textFont; }

		void setString(std::string string) { text.setString(string); }
		void setColour(sf::Color colour) { text.setFillColor(colour); }
		void setPosition(sf::Vector2f position) { text.setPosition(position); }
		int getMoveSpeed() { return moveSpeed; }
		int getLifetime() { return lifetime; }
		void setLifetime(int lifetime) { this->lifetime = lifetime; }
	private:
		sf::Text text;
		sf::Font textFont;
		int lifetime;
		int moveSpeed;
	};
}