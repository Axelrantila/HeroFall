#ifndef AUDIOASSETSPATHLOADER_H
#define AUDIOASSETSPATHLOADER_H

#include <string>
#include <vector>

class AudioAssetsPathLoader
{
public:
	static std::vector<std::string> getDefaultSoundPaths();
	static std::vector<std::string> getDefaultMusicPaths();
};

#endif