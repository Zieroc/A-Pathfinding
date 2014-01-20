#ifndef GAME_H
#define GAME_H
#include "Debug.h"
#include <SDL.h>

class Game
{
public:
	Game();
	~Game();
	bool Initialize(const char* title, int x, int y, int width, int height, int flags);
	void Update();
	void Draw();
	void HandleEvents();
	bool IsRunning();
	void CleanUp();
private:
	bool m_Running;
	SDL_Window* m_p_Window;
	SDL_Renderer * m_p_Renderer;;
};

#endif

