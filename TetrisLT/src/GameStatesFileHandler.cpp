#include "../h/GameStatesFileHandler.hpp"

#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>

bool GameStatesFileHandler::IsKeyUsed(SDL_Scancode key) {
	bool keyIsUsed = false;
	keyIsUsed = this->QuitKey == key ||
				this->ResetKey == key;
	return keyIsUsed;
}

bool GameStatesFileHandler::LoadFromFile() {
	std::string fileName = "game.ini";

	if (!std::filesystem::exists(fileName))
		return false;

	try {
		std::ifstream file(fileName);
		if (file.is_open()) {
			std::string line;
			while (std::getline(file, line)) {
				// parse line
				std::string delim = "=";
				std::vector<std::string> result;

				size_t found = line.find(delim);
				size_t startIndex = 0;

				while (found != std::string::npos)
				{
					result.emplace_back(std::string(line.begin() + startIndex, line.begin() + found));
					startIndex = found + delim.size();
					found = line.find(delim, startIndex);
				}
				if (startIndex != line.size())
					result.emplace_back(std::string(line.begin() + startIndex, line.end()));

				// return false if parsed line doesn't result to 2 values
				if (result.size() != 2)
					return false;

				// result[0] = member name; result[1] = member value
				std::string memberName = result[0];
				std::string strMemberValue = result[1];
				if (memberName == "SelectedTetrisSettingName")
					this->SelectedTetrisSettingName = strMemberValue;
				else if (memberName == "SFXVolume")
					this->SFXVolume = std::stoi(strMemberValue);
				else if (memberName == "QuitKey")
					this->QuitKey = (SDL_Scancode)std::stoi(strMemberValue);
				else if (memberName == "ResetKey")
					this->ResetKey = (SDL_Scancode)std::stoi(strMemberValue);
				else if (memberName == "StartCountdownTicks")
					this->StartCountdownTicks = std::stoi(strMemberValue);
				else if (memberName == "StartCountdownTickDurationMS")
					this->StartCountdownTickDurationMS = std::stoi(strMemberValue);
				else if (memberName == "ResetCountdownTicks")
					this->ResetCountdownTicks = std::stoi(strMemberValue);
				else if (memberName == "ResetCountdownTickDurationMS")
					this->ResetCountdownTickDurationMS = std::stoi(strMemberValue);
				else if (memberName == "GameFinishDelayMS")
					this->GameFinishDelayMS = std::stoi(strMemberValue);
				
			}
			file.close();
		}
	}
	catch (...) {
		return false;
	}
}

void GameStatesFileHandler::WriteToFile() {
	std::string fileName = "game.ini";

	// delete old game states
	if (std::filesystem::exists(fileName))
		std::filesystem::remove(fileName);

	// create new setting
	std::ofstream newGameSetting;
	newGameSetting.open(fileName);
	newGameSetting << "SFXVolume=" << SFXVolume << '\n';
	newGameSetting << "SelectedTetrisSettingName=" << SelectedTetrisSettingName << '\n';
	newGameSetting << "QuitKey=" << QuitKey << '\n';
	newGameSetting << "ResetKey=" << ResetKey << '\n';
	newGameSetting << "StartCountdownTicks=" << StartCountdownTicks << '\n';
	newGameSetting << "StartCountdownTickDurationMS=" << StartCountdownTickDurationMS << '\n';
	newGameSetting << "ResetCountdownTicks=" << ResetCountdownTicks << '\n';
	newGameSetting << "ResetCountdownTickDurationMS=" << ResetCountdownTickDurationMS << '\n';
	newGameSetting << "GameFinishDelayMS=" << GameFinishDelayMS << '\n';

	newGameSetting.close();
}