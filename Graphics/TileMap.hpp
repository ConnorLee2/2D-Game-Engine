#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>

/*
	Tilemap class
	Code taken from the sfml tutorials site, with some modifications
*/


namespace GameEngine
{
	class TileMap : public sf::Drawable, public sf::Transformable
	{
	public:
		bool load(const std::string& texture, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height);
		int getTile(int i);
		int getGridX(int i);
		int getGridY(int i);
		void setTile(int i, int tileType);
		int getTileByType(int i);

	private:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		sf::VertexArray vertices;
		sf::Texture tileset;
		int tilesArray[256];
	};
}