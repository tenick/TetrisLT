#include "../../h/UI/Results.hpp"

class Results {
public:
	
private:
	TetrisStats currStats;
};

namespace UI {
	void Results::Show() {
		this->isShowing = true;
	}
	void Results::Hide() {
		this->isShowing = false;
	}
	bool Results::IsShowing() {
		return this->isShowing;
	}
	void Results::Update() {

	}
	void Results::Render() {

	}
	void Results::UpdateStats(TetrisStats newStats) {
		this->currStats = newStats;
	}
}
