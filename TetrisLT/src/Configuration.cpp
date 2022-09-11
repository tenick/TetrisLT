#include "../h/Configuration.hpp"

namespace Configuration {
    // game states and loaded settings
    std::vector<TetrisSettingsFileHandler>* LoadedTetrisSettings = nullptr;
    GameStatesFileHandler* LastGameStates = nullptr;

    TetrisSettingsFileHandler& CurrentSelectedTetrisSetting() {
		int i = 0;
		for (auto& tetrisSetting : *LoadedTetrisSettings)
			if (tetrisSetting.SettingName == LastGameStates->SelectedTetrisSettingName) {
				return tetrisSetting;
		}
    }
}