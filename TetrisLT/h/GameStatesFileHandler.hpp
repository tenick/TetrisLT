#ifndef GAME_STATES_FILE_HANDLER_H
#define GAME_STATES_FILE_HANDLER_H

#include <string>

struct GameStatesFileHandler {
	int SFXVolume = 80;
	std::string SelectedTetrisSettingName;

	bool LoadFromFile();
	void WriteToFile();
};

#endif