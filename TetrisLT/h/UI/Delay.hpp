#ifndef DELAY_H
#define DELAY_H

#include "../Timer.hpp"

namespace UI {
	class Delay {
	public:
		Delay(int ticks=3, int tickDurationInMS=3, bool showCountdown=false);
		void Show();
		void Update();
		void Hide();
		bool IsShowing();
	private:
		Timer timer;
		int startTime = 0;
		int ticks = 3;
		int tickDurationInMS = 3;
		bool showCountdown = false; // will need render() for this
		bool isShowing = false;
	};
}

#endif