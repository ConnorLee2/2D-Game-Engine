#include "AudioManager.hpp"

namespace GameEngine
{
	void AudioManager::playSoundEffect(sf::SoundBuffer buffer)
	{
		this->buffer = buffer;
		soundEffect.setBuffer(this->buffer);
		soundEffect.play();
	}

	void AudioManager::playBGM(std::string fileName)
	{
		if (!BGM.openFromFile(fileName))
		{
			std::cout << "Error playing BGM: " << fileName << std::endl;
		}

		BGM.play();
	}

	void AudioManager::setBGMVolume(int number)
	{
		BGM.setVolume(number);
	}

	void AudioManager::loopBGM(bool boolean)
	{
		BGM.setLoop(boolean);
	}
}