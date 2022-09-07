#ifndef DELAY_H
#define DELAY_H

#include "../Timer.hpp"

namespace UI {
	class Delay {
	public:
		Delay(int ticks=3, int tickDurationInMS=1000, bool showCountdown=true);
		void Show();
		void Show(int ticks, int tickDurationInMS, bool showCountdown);
		void Update();
		void Render();
		void Hide();
		bool IsShowing();
	private:
		Timer timer;
		int startTime = 0;
		int ticks = 3;
		int tickDurationInMS = 3;
		bool showCountdown = true;
		bool isShowing = false;
	};
}

#endif