#ifndef AUDIOLOADER_H
#define AUDIOLOADER_H

#include <SFML\Audio.hpp>

#include <map>
#include <string>
#include <vector>

typedef std::string string;

typedef std::map<string, std::vector<sf::SoundBuffer*>> soundBufferMap;
typedef std::map<string, std::vector<sf::Sound*>> soundMap;
typedef std::map<string, sf::Music*> musicMap;

class Util;

class AudioLoader
{
public:
	AudioLoader();
	~AudioLoader();

	int loadSound(string name, string audioPath);
	sf::Sound* getSound(string name);

	int loadMusic(string name, string AudioPath);
	sf::Music* getMusic(string name);

	void loadAllSounds();

private:
	soundMap m_sounds;
	soundBufferMap m_soundBuffers;
	musicMap m_musics;
};

#endif AUDIOLOADER_H