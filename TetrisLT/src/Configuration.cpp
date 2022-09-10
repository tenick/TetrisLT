#include "../h/Configuration.hpp"

namespace Configuration {
    // game states and loaded settings
    std::vector<TetrisSettingsFileHandler>* LoadedTetrisSettings = nullptr;
    GameStatesFileHandler* LastGameStates = nullptr;
}