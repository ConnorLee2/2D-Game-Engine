#pragma once
#include <map>
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <iostream>

/*
	Controls loading and unloading of assets, stores assets
	which can be reused
*/


namespace GameEngine
{
	class AssetManager
	{
	public:
		AssetManager() {}
		~AssetManager() {}

		void LoadTexture(std::string name, std::string fileName);
		sf::Texture &GetTexture(std::string name);
		void UnloadTexture(std::string name);

		void LoadFont(std::string name, std::string fileName);
		sf::Font &GetFont(std::string name);
		void UnloadFont(std::string name);

		void LoadSoundEffect(std::string name, std::string fileName);
		sf::SoundBuffer &GetSoundEffect(std::string name);
		void UnloadSoundEffect(std::string name);
		void CleanUp();

	private:
		// unordered maps
		// look into removing assets after not needing it after awhile? (lifetime of an asset)
		std::map<std::string, sf::Texture> textures;
		std::map<std::string, sf::Font> fonts;
		std::map<std::string, sf::SoundBuffer> soundEffects;
	};
}