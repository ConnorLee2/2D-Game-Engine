#pragma once
#include <SFML\Audio.hpp>
#include <iostream>

/*
	Allows the engine to give audio cues and play background music
*/


namespace GameEngine
{
	class AudioManager
	{
	public:
		AudioManager() {};
		~AudioManager() {};

		void playSoundEffect(sf::SoundBuffer buffer);
		void playBGM(std::string fileName);
		void setBGMVolume(int number);
		void loopBGM(bool boolean);

	private:
		sf::Music BGM;
		sf::SoundBuffer buffer;
		sf::Sound soundEffect;
	};
}
