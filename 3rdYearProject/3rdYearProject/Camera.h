#ifndef CAMERA_H
#define CAMERA_H
#include "Debug.h"
#include <SDL.h>

#define DEFAULT_RATIO 50.0f

class Camera
{
public:
	Camera(float x, float y, float width, float height, SDL_Rect levelRect);
	~Camera();
	void Move(float x, float y);
	bool IsObjectVisible(SDL_Rect objectBounds);
	float XLocationToScreen(float Xlocation); //Map a world location to the screen
	float YLocationToScreen(float Ylocation); //Map a world location to the screen
	SDL_Rect LocationToScreen(SDL_Rect location);
	float XScreenToLocation(float Xlocation); //Map a screen location to the world
	float YScreenToLocation(float Ylocation); //Map a screen location to the world
	SDL_Rect ScreenToLocation(SDL_Rect location);
	float GetPositionX();
	float GetPositionY();
	float GetViewPortW();
	float GetViewPortH();
private:
	float m_PositionX; //Viewport position - Keep as a seperate vector to allow for floats rather than ints
	float m_PositionY;
	float m_ViewPortW; //Viewport width and height - Keep as a seperate vector to allow for floats rather than ints
	float m_ViewPortH;
	SDL_Rect m_LevelRectangle; //The size of the game's level
	void CalcViewPort(float amount); //Different pixel to unit ratios will mean the viewport shows a different amount of the screen so the size needs to be recalculated
};

#endif
