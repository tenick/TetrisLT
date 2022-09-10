#include "../h/TetrisSettingsFileHandler.hpp"

#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>

bool TetrisSettingsFileHandler::IsKeyUsed(SDL_Scancode key) {
	bool keyIsUsed = false;
	keyIsUsed = this->MoveLeft == key ||
				this->MoveRight == key ||
				this->SoftDrop == key ||
				this->HardDrop == key ||
				this->HoldTetrominoKey == key ||
				this->RotateCW == key ||
				this->RotateCCW == key ||
				this->Rotate180 == key;
	return keyIsUsed;
}

bool TetrisSettingsFileHandler::LoadFromFile(std::string fileName) {
	// remove parent dir
	size_t lastindexSlash = fileName.find_last_of("\\");
	std::string fileNameWithoutExt = fileName.substr(lastindexSlash + 1, fileName.size() - 1);
	// remove file extension
	size_t lastindexDot = fileNameWithoutExt.find_last_of(".");
	fileNameWithoutExt = fileNameWithoutExt.substr(0, lastindexDot);

	// (if it doesn't exist, create default config)
	// (it it exists, but not corrupt, skip)
	if (!std::filesystem::exists(fileName))
		return false;

	try {
		std::ifstream file(fileName);
		if (file.is_open()) {
			std::string line;
			while (std::getline(file, line)) {
				// using printf() in all tests for consistency

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
				if (memberName == "PlayerName")
					this->PlayerName = strMemberValue;
				else if (memberName == "DAS")
					this->DAS = std::stoi(strMemberValue);
				else if (memberName == "ARR")
					this->ARR = std::stoi(strMemberValue);
				else if (memberName == "SDS")
					this->SDS = std::stoi(strMemberValue);
				else if (memberName == "Gravity")
					this->Gravity = std::stoi(strMemberValue);
				else if (memberName == "LockDelay")
					this->LockDelay = std::stoi(strMemberValue);
				else if (memberName == "LockDelayResetLimit")
					this->LockDelayResetLimit = std::stoi(strMemberValue);
				else if (memberName == "DelayAfterPieceLock")
					this->DelayAfterPieceLock = std::stoi(strMemberValue);

				else if (memberName == "BoardWidth")
					this->BoardWidth = std::stoi(strMemberValue);
				else if (memberName == "BoardHeight")
					this->BoardHeight = std::stoi(strMemberValue);
				else if (memberName == "VanishingZoneHeight")
					this->VanishingZoneHeight = std::stoi(strMemberValue);
				else if (memberName == "EnableGhostPiece")
					this->EnableGhostPiece = (bool)std::stoi(strMemberValue);

				else if (memberName == "MoveLeft")
					this->MoveLeft = (SDL_Scancode)std::stoi(strMemberValue);
				else if (memberName == "MoveRight")
					this->MoveRight = (SDL_Scancode)std::stoi(strMemberValue);
				else if (memberName == "SoftDrop")
					this->SoftDrop = (SDL_Scancode)std::stoi(strMemberValue);
				else if (memberName == "HardDrop")
					this->HardDrop = (SDL_Scancode)std::stoi(strMemberValue);
				else if (memberName == "HoldTetrominoKey")
					this->HoldTetrominoKey = (SDL_Scancode)std::stoi(strMemberValue);
				else if (memberName == "RotateCW")
					this->RotateCW = (SDL_Scancode)std::stoi(strMemberValue);
				else if (memberName == "RotateCCW")
					this->RotateCCW = (SDL_Scancode)std::stoi(strMemberValue);
				else if (memberName == "Rotate180")
					this->Rotate180 = (SDL_Scancode)std::stoi(strMemberValue);

				this->SettingName = fileNameWithoutExt;
			}
			file.close();
		}
	}
	catch (...) {
		return false;
	}
}

void TetrisSettingsFileHandler::WriteToFile() {
	std::string newFileName = "config/" + this->SettingName + ".ini";


	// create new setting
	std::ofstream newFileSetting;
	newFileSetting.open(newFileName);
	newFileSetting << "PlayerName=" << PlayerName << '\n';

	newFileSetting << "DAS=" << DAS << '\n';
	newFileSetting << "ARR=" << ARR << '\n';
	newFileSetting << "SDS=" << SDS << '\n';
	newFileSetting << "Gravity=" << Gravity << '\n';
	newFileSetting << "LockDelay=" << LockDelay << '\n';
	newFileSetting << "LockDelayResetLimit=" << LockDelayResetLimit << '\n';
	newFileSetting << "DelayAfterPieceLock=" << DelayAfterPieceLock << '\n';

	newFileSetting << "BoardWidth=" << BoardWidth << '\n';
	newFileSetting << "BoardHeight=" << BoardHeight << '\n';
	newFileSetting << "VanishingZoneHeight=" << VanishingZoneHeight << '\n';
	newFileSetting << "EnableGhostPiece=" << EnableGhostPiece << '\n';

	newFileSetting << "MoveLeft=" << MoveLeft << '\n';
	newFileSetting << "MoveRight=" << MoveRight << '\n';
	newFileSetting << "SoftDrop=" << SoftDrop << '\n';
	newFileSetting << "HardDrop=" << HardDrop << '\n';
	newFileSetting << "HoldTetrominoKey=" << HoldTetrominoKey << '\n';
	newFileSetting << "RotateCW=" << RotateCW << '\n';
	newFileSetting << "RotateCCW=" << RotateCCW << '\n';
	newFileSetting << "Rotate180=" << Rotate180 << '\n';

	newFileSetting.close();

}