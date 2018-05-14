#include "TileMap.hpp"

namespace GameEngine
{
	bool TileMap::load(const std::string & texture, sf::Vector2u tileSize, const int * tiles, unsigned int width, unsigned int height)
	{
		// load the tileset texture
		if (!tileset.loadFromFile(texture))
			return false;

		// resize the vertex array to fit the level size
		vertices.setPrimitiveType(sf::Quads);
		vertices.resize(width * height * 4);

		// populate the vertex array, with one quad per tile
		for (unsigned int i = 0; i < width; ++i)
		{
			for (unsigned int j = 0; j < height; ++j)
			{
				// get the current tile number
				int tileNumber = tiles[i + j * width];

				// Initialise tiles array
				tilesArray[(i*width) + j] = tiles[(i * width) + j];
				std::cout << i << "," << j << " : " << tilesArray[i] << std::endl;

				// find its position in the tileset texture
				int tu = tileNumber % (tileset.getSize().x / tileSize.x);
				int tv = tileNumber / (tileset.getSize().x / tileSize.x);

				// get a pointer to the current tile's quad
				sf::Vertex* quad = &vertices[(i + j * width) * 4];

				// define its 4 corners
				quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
				quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
				quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
				quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

				// define its 4 texture coordinates
				quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
				quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
				quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
				quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
			}
		}
		return true;
	}

	int TileMap::getTile(int i)
	{
		return tilesArray[i];
	}

	void TileMap::draw(sf::RenderTarget & target, sf::RenderStates states) const
	{
		// apply the transform
		states.transform *= getTransform();

		// apply the tileset texture
		states.texture = &tileset;

		// draw the vertex array
		target.draw(vertices, states);
	}

	int TileMap::getGridX(int i)
	{
		return i % 16;
	}

	int TileMap::getGridY(int i)
	{
		return i / 16;
	}

	int TileMap::getTileByType(int i)
	{
		// 0 to 6
		// 0 cobble
		// 1 wall
		// 2 grass (end game)
		// 3 start position
		// 4 acid
		// 5 movable bricks
		int* searchArray = std::find(std::begin(tilesArray), std::end(tilesArray), i);
		if (searchArray != std::end(tilesArray))
		{
			return std::distance(tilesArray, searchArray);
		}
		else
		{
			return -1;
		}
	}
}