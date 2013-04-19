#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H

#include "SettingsObject.h"

class SettingsManager
{
public:
	static SettingsManager* getInstance();
	static SettingsObject* getSettings();

	bool loadSettings();
	bool saveSettings();
private:
	SettingsManager();
	~SettingsManager();

	SettingsObject* m_settings;
};

#endif