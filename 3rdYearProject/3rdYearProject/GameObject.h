#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Sprite.h"
#include "TileMap.h"
#include "Pathfinder.h"
#include "Vector2.h"
#include <SDL.h>

#define MAX_SPRITE 1

class GameObject
{
public:
	GameObject();
	GameObject(Vector2 position, int speed);
	virtual ~GameObject();
	void Initialize(Sprite* sprites[]);
	void Update(Uint32 timeElapsed);
	void Draw(SDL_Renderer* renderer, Camera* camera);
	Vector2 GetPosition();
	Vector2 GetVelocity();
	int GetSpeed();
	SDL_Rect GetBounds();
	void SetPosition(Vector2 position);
	void SetVelocity(Vector2 velocity);
	void SetSpeed(int speed);
	void SetBounds(int width, int height);
	void CalcBounds();
protected:

	Vector2 m_Position;
	Vector2 m_Velocity;
	int m_Speed;
	SDL_Rect m_Bounds;
	Sprite* m_p_Sprites[MAX_SPRITE];
	Sprite* m_p_CurrentSprite;
};

#endif

