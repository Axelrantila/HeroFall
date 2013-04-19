#include "AudioAssetsPathLoader.h"
#include "AudioLoader.h"
#include "Util.h"

#pragma region Constructors
	AudioLoader::AudioLoader()
	{
	}

	AudioLoader::~AudioLoader()
	{
		for(soundMap::iterator it = m_sounds.begin(); it != m_sounds.end(); ++it)
		{
			if(it->second.empty())
			{continue;}

			for(unsigned int a = 0; a < it->second.size(); a++)
			{
				delete it->second[a];
			}
		}

		for(soundBufferMap::iterator it = m_soundBuffers.begin(); it != m_soundBuffers.end(); ++it)
		{
			if(it->second.empty())
			{continue;}

			for(unsigned int a = 0; a < it->second.size(); a++)
			{
				delete it->second[a];
			}
		}

		for(musicMap::iterator it = m_musics.begin(); it != m_musics.end(); ++it)
		{
			delete it->second;
		}
	}
#pragma endregion

#pragma region Publics
	int AudioLoader::loadSound(string name, string audioPath)
	{
		//Load in the sound in question to the buffer map
		sf::SoundBuffer* buffer = new sf::SoundBuffer();
		bool loaded = buffer->loadFromFile(audioPath);

		if(!loaded)
		{
			delete buffer;
			return -1;
		}
		m_soundBuffers[name].push_back(buffer);

		//Set the sound buffer to a sound object;
		sf::Sound* sound = new sf::Sound(*m_soundBuffers[name].at(m_soundBuffers[name].size()-1));
		m_sounds[name].push_back(sound);

		return 0;
	}

	sf::Sound* AudioLoader::getSound(string name)
	{
		if(m_sounds[name].empty())
		{return nullptr;}

		else
		{
			unsigned int element = (unsigned int)Util::getInstance()->getRandomFloat(0.0f, (float)m_sounds[name].size());
			if(element == m_sounds[name].size())
			{element--;}
			return m_sounds[name][element];
		}
	}

	int AudioLoader::loadMusic(string name, string audioPath)
	{
		if(m_musics[name] != nullptr)
		{return -1;}

		sf::Music* music = new sf::Music();
		bool opened = music->openFromFile(audioPath);

		if(!opened)
		{
			delete music;
			return -2;
		}

		m_musics[name] = music;

		return 0;
	}

	sf::Music* AudioLoader::getMusic(string name)
	{
		return m_musics[name];
	}

	void AudioLoader::loadAllSounds()
	{
		//Get all the soundPaths
		std::vector<string> soundPaths = AudioAssetsPathLoader::getDefaultSoundPaths();
		for(unsigned int a = 0; a < soundPaths.size(); a++)
		{
			for(unsigned int b = 0; b < soundPaths[a].length()-1;)
			{
				if(soundPaths[a][b] == '\\' && soundPaths[a][b+1] == '\\')
				{
					b += 2;
				}
				else if(soundPaths[a][b] == '\\' && soundPaths[a][b+1] != '\\')
				{
					soundPaths[a].insert(soundPaths[a].begin() + b, '\\');
					b += 2;
				}
				else
				{
					b++;
				}
			}
		}
		//Load all the sounds
		//Check if it is in a folder or not

		for(unsigned int a = 0; a < soundPaths.size(); a++)
		{
			string tempFilePath = soundPaths[a];
			tempFilePath = tempFilePath.substr(tempFilePath.find_first_of("\\\\") + 2);
			tempFilePath = tempFilePath.substr(tempFilePath.find_first_of("\\\\") + 2);
			tempFilePath = tempFilePath.substr(0, tempFilePath.find_last_of("."));

			//If it is not located in a folder
			if(tempFilePath.find_first_of("\\\\") == std::string::npos)
			{
				if(loadSound(tempFilePath, soundPaths[a]) != 0)
				{ std::cout << "Could load the sound " << soundPaths[a] << std::endl;}
			}

			//If it is
			else
			{
				tempFilePath = tempFilePath.substr(0, tempFilePath.find_first_of("\\\\"));
				if(loadSound(tempFilePath, soundPaths[a]) != 0)
				{ std::cout << "Could load the sound " << soundPaths[a] << std::endl;}
			}
		}

		//Open the music files
		//Get all the musicPaths
		std::vector<string> musicPaths = AudioAssetsPathLoader::getDefaultMusicPaths();
		for(unsigned int a = 0; a < musicPaths.size(); a++)
		{
			for(unsigned int b = 0; b < musicPaths[a].length()-1;)
			{
				if(musicPaths[a][b] == '\\' && musicPaths[a][b+1] == '\\')
				{
					b += 2;
				}
				else if(musicPaths[a][b] == '\\' && musicPaths[a][b+1] != '\\')
				{
					musicPaths[a].insert(musicPaths[a].begin() + b, '\\');
					b += 2;
				}
				else
				{
					b++;
				}
			}
		}

		for(unsigned int a = 0; a < musicPaths.size(); a++)
		{
			string tempFilePath = musicPaths[a];
			tempFilePath = tempFilePath.substr(tempFilePath.find_first_of("\\\\") + 2);
			tempFilePath = tempFilePath.substr(tempFilePath.find_first_of("\\\\") + 2);
			tempFilePath = tempFilePath.substr(0, tempFilePath.find_last_of("."));
			loadMusic(tempFilePath, musicPaths[a]);
		}
	}
#pragma endregion