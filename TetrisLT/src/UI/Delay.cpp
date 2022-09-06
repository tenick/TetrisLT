#include "../../h/UI/Delay.hpp"
#include <SDL.h>

namespace UI {
	Delay::Delay(int ticks, int tickDurationInMS, bool showCountdown)
		: ticks(ticks), tickDurationInMS(tickDurationInMS), showCountdown(showCountdown)
	{}

	void Delay::Show() {
		this->isShowing = true;
		this->timer.Restart();
		this->startTime = timer.CurrentTick();
	}

	void Delay::Update() {
		if (timer.CurrentTick() - this->startTime > this->ticks * this->tickDurationInMS)
			this->Hide();
	}

	void Delay::Hide() {
		this->isShowing = false;
	}
	bool Delay::IsShowing() {
		return this->isShowing;
	}
}