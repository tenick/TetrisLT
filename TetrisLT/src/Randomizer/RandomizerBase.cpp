#include "../../h/Randomizer/RandomizerBase.hpp"

namespace Randomizer {
	RandomizerBase::RandomizerBase() // when unresolved external error points here, do this:
	{// remove the line below, start, then put it back again, then start again, until it works
		this->SetSeed(this->seed);
	}// a fix that i can think of for this is making different projects for different tetris systems (randomizer, rotation, etc)

	void RandomizerBase::SetSeed(int seed) {
		this->seed = seed;
		RNG.seed(seed);
	}
}