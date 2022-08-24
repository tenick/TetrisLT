#pragma once
#include <SDL.h>

class Timer {
public:
	void Start();
	void Stop();

private:
	bool isStarted;
};