#ifndef TETRIS_STATS_H
#define TETRIS_STATS_H

struct TetrisStats {
	int LinesCleared = 0;
	int PiecesLocked = 0;
	float PPS = 0;
	int gameDurationInMS = 0;
};

#endif