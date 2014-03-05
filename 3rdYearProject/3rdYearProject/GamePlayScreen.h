#ifndef GAMEPLAYSCREEN_H
#define GAMEPLAYSCREEN_H
#include "GameScreen.h"
//#include "Character.h"
#include "TileMap.h"
#include "InputHandler.h"
#include "LevelMap.h"

#include "GameObject.h"

class GameplayScreen : public GameScreen
{
public:
	GameplayScreen();
	~GameplayScreen();
	void Initialize(ScreenManager* manager);
	void LoadContent(ContentManager* conMan);
	void UnloadContent();
	void Update(Uint32 timeElapsed);
	void Draw(SDL_Renderer* renderer);
	void HandleInput(InputHandler* input);
	void HandleEvents(SDL_Event sdlEvent);
private:
	LevelMap* m_p_Map;
	bool pressed;
	GameObject* m_p_Object;
	GameObject* m_p_Object2;
};

#endif