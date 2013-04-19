#ifndef AUDIOMIXER_H
#define AUDIOMIXER_H

#include "GameObject.h"

#include <SFML\Audio.hpp>

class AudioLoader;

typedef std::vector<sf::Sound*> soundVector;

struct SoundFadeInfo
{
	float fadeInTime;
	float fadeOutTime;
	float currentTimePos;
	float initVolume;
	float maxVolume;
	GameObject* gameObject;
	bool globalSound;
};

struct TrackFadeInfo
{
	bool isLooping;
	float fadeInTime;
	float currentTimePos;
	float initVolume;
	float maxVolume;
	bool hasFadedIn;
};

struct CrossfadeInfo
{
	bool isCrossfading;
	float crossfadePosition;
	float crossfadeLength;
	float maxVolume;
	bool shouldLoop;
};

class AudioMixer
{
private:
	AudioMixer();
	~AudioMixer();

public:
	static AudioMixer* getInstance();

	void setAudioLoader(AudioLoader* audioLoader);
	void update();

	/*Plays a sound that fades in to a certain volume and out in the end.
	All times is done in seconds. 0 means that there is no fade
	0 on volume means muted, 100 means full volume */
	void playSound(std::string soundName);
	void playSound(std::string soundName, float pitch);
	void playSound(std::string soundName, GameObject* gameObject, float attenuation);
	void playSound(std::string soundName, GameObject* gameObject, float attenuation, float pitch);
	void playSound(std::string soundName, float fadeInTime, float fadeOutTime, float initVolume, float maxVolume, sf::Vector2f position, float minDistance, float attenuation);
	void playSound(std::string soundName, float fadeInTime, float fadeOutTime, float initVolume, float maxVolume, float xpos, float ypos, float minDistance, float attenuation, float pitch);
	void playSound(std::string soundName, float fadeInTime, float fadeOutTime, float initVolume, float maxVolume, GameObject* gameObject, float minDistance, float attenuation, float pitch);
	void playSound(std::string soundName, float fadeInTime, float fadeOutTime, float initVolume, float maxVolume, GameObject* gameObject, float xpos, float ypos, float minDistance, float attenuation, float pitch);

	void playGlobalSound(std::string soundName);
	void playGlobalSound(std::string soundName, float pitch);
	void playGlobalSound(std::string soundName, float fadeTime, float pitch); // FadesInOut
	void playGlobalSound(std::string soundName, float fadeTime, float pitch, float volume);

	void stopAllSounds();
	void removeSound(GameObject* gameObject);
	void muteSounds(bool muteSounds);
	unsigned int getCurrentlyPlayingSoundsNumbers();
	void pauseAllSounds(bool paused);

	void playMusic(std::string soundName, float fadeInTime, float initVolume, float maxVolume, bool shouldLoop = false);
	void fadeToTrack(std::string newTrackName, float crossFadeTime, float newMaxVolume, bool loop = false);
	bool isCrossfading();
	void stopMusic();
	void muteMusic(bool muteMusic);
	void fadeOutCurrentSong(float fadeOutTime);
	float getTimeLeftCurrentTrack();

	void setListenerPosition(float xpos, float ypos);
	void setListenerDirection(float xdir, float ydir);
	void setGlobalVolume(float volume);
	void resetGlobalVolume();
	
private:
	AudioLoader* m_audioLoader;

	soundVector m_currentlyPlayingSounds;
	std::vector<SoundFadeInfo> m_soundFadeInfos;
	std::vector<float> m_soundLengths;

	std::string m_currentTrackName;
	std::string m_nextTrackName;

	sf::Music* m_currentTrack;
	sf::Music* m_nextTrack;
	TrackFadeInfo m_trackFadeInfo;
	CrossfadeInfo m_crossfadeInfo;
	sf::Clock m_crossfadeClock;
};

#endif