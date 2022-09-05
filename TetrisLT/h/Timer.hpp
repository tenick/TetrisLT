#ifndef TIMER_H
#define TIMER_H

#include <SDL.h>

class Timer {
public:
	void Restart();
	int CurrentTick() const;
private:
	int startTick = SDL_GetTicks64();
};

#endif