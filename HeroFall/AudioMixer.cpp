#include "AudioLoader.h"
#include "AudioMixer.h"
#include <iostream>

#pragma region Constructors
	AudioMixer::AudioMixer()
	{
		m_audioLoader = new AudioLoader();
		m_audioLoader->loadAllSounds();
		m_currentTrack = nullptr;
		m_crossfadeInfo.isCrossfading = false;
		m_nextTrack = nullptr;

		m_currentTrackName = "";
		m_nextTrackName = "";

		//Set global volym
	}

	AudioMixer::~AudioMixer()
	{
		for(unsigned int a = 0; a < m_currentlyPlayingSounds.size(); a++)
		{
			m_currentlyPlayingSounds[a]->stop();
			delete m_currentlyPlayingSounds[a];
		}
		delete m_audioLoader;
	}
#pragma endregion

#pragma region Publics
	AudioMixer* AudioMixer::getInstance()
	{
		static AudioMixer instance;
		return &instance;
	}

	void AudioMixer::setAudioLoader(AudioLoader* audioLoader)
	{
		m_audioLoader = audioLoader;
	}

	void AudioMixer::stopAllSounds()
	{
		for(unsigned int a = 0; a < m_currentlyPlayingSounds.size() ; a++)
		{
			m_currentlyPlayingSounds[a]->stop();
		}
	}

	void AudioMixer::setGlobalVolume(float volume)
	{
		sf::Listener::setGlobalVolume(volume);
	}

	void AudioMixer::resetGlobalVolume()
	{
		sf::Listener::setGlobalVolume(100.0f);
	}

#pragma region update
	void AudioMixer::update()
	{
		if(m_currentTrack != nullptr)
		{
			//Crossfade music
			if(m_crossfadeInfo.isCrossfading)
			{		
				m_crossfadeInfo.crossfadePosition = m_crossfadeClock.getElapsedTime().asSeconds();

				if(m_crossfadeInfo.crossfadePosition >= m_crossfadeInfo.crossfadeLength)
				{
					m_crossfadeInfo.isCrossfading = false;
					m_currentTrack->stop();
					m_currentTrack = m_nextTrack;
					m_currentTrackName = m_nextTrackName;
					m_currentTrack->setVolume(m_crossfadeInfo.maxVolume);
					m_nextTrack = nullptr;

					m_trackFadeInfo.maxVolume = m_crossfadeInfo.maxVolume;
				}

				else
				{
					float oldSongVolume = m_trackFadeInfo.maxVolume *
						(1 - (m_crossfadeInfo.crossfadePosition / m_crossfadeInfo.crossfadeLength));
					m_currentTrack->setVolume(oldSongVolume);

					//Fade in the new one
					float newSongVolume = m_crossfadeInfo.maxVolume * (m_crossfadeInfo.crossfadePosition / m_crossfadeInfo.crossfadeLength);
					m_nextTrack->setVolume(newSongVolume);
				}
			}
			else
			{
				//Update the background song
				if(!m_trackFadeInfo.hasFadedIn)
				{
					m_trackFadeInfo.currentTimePos = m_currentTrack->getPlayingOffset().asSeconds();

					if(m_trackFadeInfo.currentTimePos >= m_trackFadeInfo.fadeInTime)
					{
						m_currentTrack->setVolume(m_trackFadeInfo.maxVolume);
						m_trackFadeInfo.hasFadedIn = true;
					}
					else
					{
						float newVolume = m_trackFadeInfo.initVolume + 
						(m_trackFadeInfo.maxVolume - m_trackFadeInfo.initVolume) * (m_trackFadeInfo.currentTimePos / m_trackFadeInfo.fadeInTime);
						m_currentTrack->setVolume(newVolume);
					}	
				}
				else if(m_currentTrackName == "Silence_30Second")
				{
					m_currentTrack->stop();
					m_currentTrack = nullptr;
				}
			}
		}

		if(!m_currentlyPlayingSounds.empty())
		{
			//Update sounds
			for(int a = (int)(m_currentlyPlayingSounds.size() - 1); a >= 0; a--)
			{
				//Delete any sounds that isn't playing anymore
				if(m_currentlyPlayingSounds[a]->getStatus() == sf::Sound::Stopped)
				{
					delete m_currentlyPlayingSounds[a];
					m_currentlyPlayingSounds.erase(m_currentlyPlayingSounds.begin() + a);
					m_soundFadeInfos.erase(m_soundFadeInfos.begin() + a);
					m_soundLengths.erase(m_soundLengths.begin() + a);

					continue;
				}

				m_soundFadeInfos[a].currentTimePos = m_currentlyPlayingSounds[a]->getPlayingOffset().asSeconds();

				//Change position of sounds that can do so
				if(m_soundFadeInfos[a].gameObject != nullptr)
				{
					m_currentlyPlayingSounds[a]->setPosition(m_soundFadeInfos[a].gameObject->getXPos(), 0, m_soundFadeInfos[a].gameObject->getYPos());
				}

				/*if(_soundFadeInfos[a].globalSound)
				{
					//_currentlyPlayingSounds[a]->setPosition(sf::Listener::getDirection());
				}*/

				//Fade in any sounds that is supposed to fade in
				if(m_soundFadeInfos[a].fadeInTime > 0.0f
					&& m_soundFadeInfos[a].currentTimePos < m_soundFadeInfos[a].fadeInTime
					&& m_soundFadeInfos[a].fadeInTime <= m_soundLengths[a])
				{
					if(m_soundFadeInfos[a].currentTimePos > m_soundFadeInfos[a].fadeInTime)
					{
						m_soundFadeInfos[a].currentTimePos = m_soundFadeInfos[a].fadeInTime;
					}

					float newVolume = m_soundFadeInfos[a].initVolume + 
						(m_soundFadeInfos[a].maxVolume - m_soundFadeInfos[a].initVolume) * (m_soundFadeInfos[a].currentTimePos / m_soundFadeInfos[a].fadeInTime);
					m_currentlyPlayingSounds[a]->setVolume(newVolume);
				}

				//Fade out any sound that should faded out
				if( m_soundFadeInfos[a].fadeOutTime > 0.0f 
					&& m_soundFadeInfos[a].fadeInTime + m_soundFadeInfos[a].fadeOutTime <= m_soundLengths[a]
					&& m_soundLengths[a] - m_soundFadeInfos[a].currentTimePos <= m_soundFadeInfos[a].fadeOutTime)
				{
					float newVolume = m_soundFadeInfos[a].maxVolume - 
						(m_soundFadeInfos[a].maxVolume - m_soundFadeInfos[a].initVolume)
						*(m_soundFadeInfos[a].currentTimePos - (m_soundLengths[a] - m_soundFadeInfos[a].fadeOutTime))/(m_soundFadeInfos[a].fadeOutTime);

					m_currentlyPlayingSounds[a]->setVolume(newVolume);
				}

				if(a == 0){break;}
			}
		}		
	}
#pragma endregion


#pragma region playsound
	void AudioMixer::playSound(string soundName)
	{
		playSound(soundName, 0.0f, 0.0f, 100.0f, 100.0f, nullptr, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f);
	}

	void AudioMixer::playSound(string soundName, float pitch)
	{
		playSound(soundName, 0.0f, 0.0f, 100.0f, 100.0f, nullptr, 0.0f, 0.0f, 1.0f, 0.0f, pitch);
	}

	void AudioMixer::playSound(string soundName, GameObject* gameObject, float attenuation)
	{
		playSound(soundName, 0.0f, 0.0f, 100.0f, 100.0f, gameObject, gameObject->getXPos(), gameObject->getYPos(), 200.f, attenuation, 1.0f);
	}

	void AudioMixer::playSound(string soundName, GameObject* gameObject, float attenuation, float pitch)
	{
		playSound(soundName, 0.0f, 0.0f, 100.0f, 100.0f, gameObject, gameObject->getXPos(), gameObject->getYPos(), 200.f, attenuation, pitch);
	}

	void AudioMixer::playSound(string soundName, float fadeInTime, float fadeOutTime, float initVolume, float maxVolume, sf::Vector2f position, float minDistance, float attenuation)
	{
		playSound(soundName, fadeInTime, fadeOutTime, initVolume, maxVolume, nullptr, position.x, position.y, minDistance, attenuation, 1.0f);
	}

	void AudioMixer::playSound(string soundName, float fadeInTime, float fadeOutTime, float initVolume, float maxVolume, float xpos, float ypos, float minDistance, float attenuation, float pitch)
	{
		playSound(soundName, fadeInTime, fadeOutTime, initVolume, maxVolume, nullptr, xpos, ypos, minDistance, attenuation, pitch);
	}

	void AudioMixer::playSound(string soundName, float fadeInTime, float fadeOutTime, float initVolume, float maxVolume, GameObject* gameObject, float minDistance, float attenuation, float pitch)
	{
		playSound(soundName, fadeInTime, fadeOutTime, initVolume, maxVolume, gameObject, gameObject->getXPos(), gameObject->getYPos(), minDistance, attenuation, pitch);
	}

	void AudioMixer::playSound(string soundName, float fadeInTime, float fadeOutTime, float initVolume, float maxVolume, GameObject* gameObject, float xpos, float ypos, float minDistance, float attenuation, float pitch)
	{
		if(m_audioLoader->getSound(soundName) == nullptr)
		{return;}

		SoundFadeInfo fadeInfo;
		fadeInfo.fadeInTime = fadeInTime;
		fadeInfo.fadeOutTime = fadeOutTime;
		fadeInfo.currentTimePos = 0.0f;
		fadeInfo.gameObject = gameObject;
		fadeInfo.globalSound = false;

		if(gameObject != nullptr)
		{
			xpos = gameObject->getXPos();
			ypos = gameObject->getYPos();
		}

		/*if(!SettingsManager::getGlobalSettings()->SOUND_SOUND)
		{
			fadeInfo.initVolume = 0.0f;
			fadeInfo.maxVolume = 0.0f;
		}
		else
		{
			if(initVolume == 100.0f)
			{
				fadeInfo.initVolume = 0.0f;
			}
			else
			{
				fadeInfo.initVolume = initVolume;
			}
			
			fadeInfo.initVolume = initVolume;
			fadeInfo.maxVolume = maxVolume;
		}
		*/
		fadeInfo.initVolume = initVolume;
		fadeInfo.maxVolume = maxVolume;

		sf::Sound* tSound = new sf::Sound(*m_audioLoader->getSound(soundName));
		tSound->setPosition(xpos, 0, ypos);
		tSound->setMinDistance(minDistance);
		tSound->setAttenuation(attenuation);
		tSound->setPitch(pitch);

		if(fadeInTime == 0.0f)
			{tSound->setVolume(fadeInfo.maxVolume);}
		else
			{tSound->setVolume(fadeInfo.initVolume);}

		tSound->play();
		m_currentlyPlayingSounds.push_back(tSound);
		m_soundFadeInfos.push_back(fadeInfo);
		m_soundLengths.push_back(m_audioLoader->getSound(soundName)->getBuffer()->getDuration().asSeconds());
	}
#pragma endregion

	void AudioMixer::playGlobalSound(string soundName)
	{
		playGlobalSound(soundName, 0.0f, 1.0f, 100.0f);
	}

	void AudioMixer::playGlobalSound(string soundName, float pitch)
	{
		playGlobalSound(soundName, 0.0f, pitch, 100.0f);
	}

	void AudioMixer::playGlobalSound(string soundName, float fadeTime, float pitch)
	{
		playGlobalSound(soundName, fadeTime, pitch, 100.0f);
	}

	void AudioMixer::playGlobalSound(string soundName, float fadeTime, float pitch, float volume)
	{
		if(m_audioLoader->getSound(soundName) == nullptr)
		{return;}

		SoundFadeInfo fadeInfo;
		fadeInfo.fadeInTime = fadeTime;
		fadeInfo.fadeOutTime = fadeTime;
		fadeInfo.currentTimePos = 0.0f;
		fadeInfo.gameObject = nullptr;
		fadeInfo.globalSound = true;

		/*if(!SettingsManager::getGlobalSettings()->SOUND_SOUND)
		{
			fadeInfo.initVolume = 0.0f;
			fadeInfo.maxVolume = 0.0f;
		}
		else
		{
		}
		*/
		fadeInfo.initVolume = 0.0f;
		fadeInfo.maxVolume = volume;
		sf::Sound* tSound = new sf::Sound(*m_audioLoader->getSound(soundName));
		//tSound->setPosition(sf::Listener::getDirection().x, 0, sf::Listener::getDirection().y);
		//tSound->setMinDistance(3000.0f);
		//tSound->setAttenuation(0.0f);
		tSound->setRelativeToListener(true);
		tSound->setPitch(pitch);

		if(fadeInfo.fadeInTime == 0.0f)
			{tSound->setVolume(fadeInfo.maxVolume);}
		else
			{tSound->setVolume(fadeInfo.initVolume);}

		tSound->play();
		m_currentlyPlayingSounds.push_back(tSound);
		m_soundFadeInfos.push_back(fadeInfo);
		m_soundLengths.push_back(m_audioLoader->getSound(soundName)->getBuffer()->getDuration().asSeconds());
	}

	void AudioMixer::removeSound(GameObject* gameObject)
	{
		if(!m_soundFadeInfos.empty())
		{
			for(unsigned int a = m_soundFadeInfos.size() - 1; a >= 0 ; a--)
			{
				if(m_soundFadeInfos[a].gameObject  == gameObject)
				{m_currentlyPlayingSounds[a]->stop();}
				if(a == 0){break;}
			}
		}
	}

	void AudioMixer::playMusic(string trackName, float fadeInTime, float initVolume, float maxVolume, bool shouldLoop)
	{
		if(m_audioLoader->getMusic(trackName) == nullptr)
		{
			return;
		}

		if(m_currentTrack != nullptr)
		{
			if(m_currentTrack->getStatus() == sf::Music::Playing)
			{m_currentTrack->stop();}
		}

		m_trackFadeInfo.fadeInTime = fadeInTime;
		m_trackFadeInfo.currentTimePos = 0.0f;
		//_trackFadeInfo.trackLength = _audioLoader->getMusic(trackName)->getDuration().asSeconds();
		m_trackFadeInfo.hasFadedIn = false;
		m_trackFadeInfo.isLooping = shouldLoop;

		/*if(!SettingsManager::getGlobalSettings()->SOUND_MUSIC)
		{
			_trackFadeInfo.initVolume = 0.0f;
			_trackFadeInfo.maxVolume = 0.0f;
		}
		else
		{
			_trackFadeInfo.initVolume = initVolume;
			_trackFadeInfo.maxVolume = maxVolume;
		}*/

		m_currentTrackName = trackName;
		m_currentTrack = m_audioLoader->getMusic(trackName);
		m_currentTrack->setVolume(initVolume);
		m_currentTrack->setLoop(shouldLoop);
		m_currentTrack->play();
	}

	void AudioMixer::fadeToTrack(string newTrackName, float crossfadeLength, float newMaxVolume, bool loop)
	{
		if(m_audioLoader->getMusic(newTrackName) == nullptr || m_currentTrack == nullptr)
		{return;}

		else if(m_currentTrack->getStatus() == sf::Sound::Stopped)
		{
			playMusic(newTrackName, crossfadeLength, 0.0f, 100.0f, loop);
			return;
		}

		float timeLeft = m_currentTrack->getDuration().asSeconds() - m_currentTrack->getPlayingOffset().asSeconds();
		if(timeLeft < crossfadeLength)
		{
			crossfadeLength = timeLeft;
		}
		
		m_crossfadeInfo.isCrossfading = true;
		m_crossfadeInfo.crossfadePosition = 0.0f;

		/*if(!SettingsManager::getGlobalSettings()->SOUND_MUSIC)
		{_crossfadeInfo.maxVolume = 0.0f;}
		else{}*/
		m_crossfadeInfo.maxVolume = newMaxVolume;
		
		m_crossfadeInfo.shouldLoop = loop;
		m_crossfadeInfo.crossfadeLength = crossfadeLength;

		m_nextTrackName = newTrackName;
		m_crossfadeClock.restart();
		m_nextTrack = m_audioLoader->getMusic(newTrackName);

		m_nextTrack->setVolume(0.0f);
		m_nextTrack->play();
	}

	void AudioMixer::setListenerPosition(float xpos, float ypos)
	{
		sf::Listener::setPosition(xpos, 0.0f, ypos);
	}

	void AudioMixer::setListenerDirection(float xdir, float ydir)
	{
		sf::Listener::setDirection(xdir, 0.0f, ydir);
	}

	unsigned int AudioMixer::getCurrentlyPlayingSoundsNumbers()
	{
		return m_currentlyPlayingSounds.size();
	}

	void AudioMixer::stopMusic()
	{
		if(m_currentTrack != nullptr)
		{m_currentTrack->stop();}
	}

	void AudioMixer::fadeOutCurrentSong(float fadeOutTime)
	{
		if(fadeOutTime > 30.0f)
		{fadeOutTime = 30.0f;}

		this->fadeToTrack("Silence_30Second", fadeOutTime, 100.0f, false);
	}

	float AudioMixer::getTimeLeftCurrentTrack()
	{
		if(m_currentTrack == nullptr)
		{return -1.0f;}
		else
		{return (m_currentTrack->getDuration().asSeconds() - m_currentTrack->getPlayingOffset().asSeconds());}
	}

	bool AudioMixer::isCrossfading()
	{
		return m_crossfadeInfo.isCrossfading;
	}

	void AudioMixer::pauseAllSounds(bool paused)
	{
		if(paused)
		{
			for(unsigned int a = 0; a < m_currentlyPlayingSounds.size(); a++)
			{
				if(m_currentlyPlayingSounds[a]->getStatus() == sf::Sound::Playing)
				{
					m_currentlyPlayingSounds[a]->pause();
				}
			}
		}

		else
		{
			for(unsigned int a = 0; a < m_currentlyPlayingSounds.size(); a++)
			{
				if(m_currentlyPlayingSounds[a]->getStatus() == sf::Sound::Paused)
				{
					m_currentlyPlayingSounds[a]->play();
				}
			}
		}
	}
#pragma endregion