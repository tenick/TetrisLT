#ifndef RESULTS_H
#define RESULTS_H

#include "../Tetromino/TetrisStats.hpp"

namespace UI {
	class Results {
	public:
		void Show();
		void Hide();
		bool IsShowing();
		void Update();
		void Render();
		void UpdateStats(TetrisStats newStats);
	private:
		TetrisStats currStats;
		bool isShowing = false;
	};
}


#endif