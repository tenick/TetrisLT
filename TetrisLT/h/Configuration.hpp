#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include "TetrisSettingsFileHandler.hpp"
#include "GameStatesFileHandler.hpp"

#include <vector>

namespace Configuration {
    // game states and loaded settings
    extern std::vector<TetrisSettingsFileHandler>* LoadedTetrisSettings;
    extern GameStatesFileHandler* LastGameStates;
}

#endif