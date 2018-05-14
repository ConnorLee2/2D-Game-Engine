#include "AssetManager.hpp"

namespace GameEngine
{
	void AssetManager::LoadTexture(std::string name, std::string fileName)
	{
		sf::Texture tex;

		if (tex.loadFromFile(fileName))
		{
			textures[name] = tex;
		}
	}

	sf::Texture &AssetManager::GetTexture(std::string name)
	{
		return textures.at(name);
	}

	void AssetManager::UnloadTexture(std::string name)
	{
		textures.erase(name);
	}

	void AssetManager::LoadFont(std::string name, std::string fileName)
	{
		sf::Font font;

		if (font.loadFromFile(fileName))
		{
			fonts[name] = font;
		}
	}

	sf::Font &AssetManager::GetFont(std::string name)
	{
		return fonts.at(name);
	}

	void AssetManager::UnloadFont(std::string name)
	{
		fonts.erase(name);
	}

	void AssetManager::LoadSoundEffect(std::string name, std::string fileName)
	{
		sf::SoundBuffer buffer;

		if (buffer.loadFromFile(fileName))
		{
			soundEffects[name] = buffer;
		}
	}

	sf::SoundBuffer & AssetManager::GetSoundEffect(std::string name)
	{
		return soundEffects.at(name);
	}

	void AssetManager::UnloadSoundEffect(std::string name)
	{
		soundEffects.erase(name);
	}

	void AssetManager::CleanUp()
	{
		// Empty textures, fonts and audio from memory
		textures.clear();
		fonts.clear();
		soundEffects.clear();
	}
}