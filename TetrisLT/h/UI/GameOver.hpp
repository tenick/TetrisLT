#ifndef GAME_OVER_H
#define GAME_OVER_H

namespace UI {
	class GameOver {
	public:
		void Show();
		bool IsShowing();
		void Hide();
		void Render();
	private:
		bool isShowing = false;
	};
}

#endif