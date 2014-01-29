#ifndef SCREENMANAGER_H
#define SCREENMANAGER_H
#include "GameScreen.h"
#include "Debug.h"
#include "ContentManager.h"
#include "InputHandler.h"
#include "Camera.h"
#include <forward_list>
#include <iostream>
#include <SDL.h>

using std::forward_list;

class ScreenManager
{
public:
	ScreenManager(SDL_Renderer* renderer, ContentManager* conMan, Camera* camera);
	~ScreenManager();
	void Initialize();
	void LoadContent();
	void UnloadContent();
	void Update(Uint32 timeElapsed);
	void HandleEvents(SDL_Event sdlEvent);
	void Draw();
	void AddScreen(GameScreen* screen, bool removePrevious);
	void AddPopup(GameScreen* popup);
	void RemoveScreen(); //Removes the last added screen
	Camera* GetCamera();
private:
	forward_list<GameScreen*> m_p_Screens;
	forward_list<GameScreen*> m_p_UpdateScreens;
	InputHandler* m_p_InputHandler;
	ContentManager* m_p_ContentManager;
	SDL_Renderer* m_p_Renderer;
	Camera* m_p_Camera;
};

#endif

