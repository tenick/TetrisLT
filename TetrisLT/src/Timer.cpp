#include "../h/Timer.hpp"

void Timer::Restart() {
	this->startTick = SDL_GetTicks64();
}
int Timer::CurrentTick() const { return SDL_GetTicks64() - this->startTick; }
