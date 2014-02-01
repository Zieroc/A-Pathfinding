#ifndef CAMERA_H
#define CAMERA_H
#include "Debug.h"
#include "Vector2.h"
#include <SDL.h>

class Camera
{
public:
	Camera(Vector2 pos, Vector2 size, SDL_Rect levelRect);
	~Camera();
	void Move(Vector2 amount);
	bool IsObjectVisible(SDL_Rect objectBounds);
	Vector2 LocationToScreen(Vector2 location); //Map a world location to the screen
	SDL_Rect LocationToScreen(SDL_Rect location);
	Vector2 ScreenToLocation(Vector2 location); //Map a screen location to the world
	SDL_Rect ScreenToLocation(SDL_Rect location);
	Vector2 GetPosition();
	Vector2 GetViewPortSize();
private:
	Vector2 m_Position; //Viewport position - Keep as a seperate vector to allow for floats rather than ints
	Vector2 m_ViewPortSize; //Viewport width and height - Keep as a seperate vector to allow for floats rather than ints
	SDL_Rect m_LevelRectangle; //The size of the game's level};
};

#endif
