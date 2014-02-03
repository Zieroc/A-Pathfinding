#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Component.h"
#include "GraphicsComponent.h"
#include "PhysicsComponent.h"
#include "InputComponent.h"
#include "Vector2.h"
#include <SDL.h>

#define MAX_COMPONENTS 3

class GameObject
{
public:
	GameObject();
	GameObject(Vector2 position, int speed);
	~GameObject();
	void Send(int message);
	void AddComponent(Component* component, int type);
	void Initialize(Component* graphics, Component* physics, Component* input);
	void InitializeGraphics(Sprite* sprites[]);
	void InitializePhysics(TileMap* map);
	void HandleInput(InputHandler* input);
	void Update(Uint32 timeElapsed);
	void Draw(SDL_Renderer* renderer, Camera* camera);
	Component* GetComponent(int type);
	Vector2 GetPosition();
	Vector2 GetVelocity();
	int GetSpeed();
	SDL_Rect GetBounds();
	void SetPosition(Vector2 position);
	void SetVelocity(Vector2 velocity);
	void SetSpeed(int speed);
	void SetBounds(int width, int height);
	void CalcBounds();
private:
	Component* m_p_Components[MAX_COMPONENTS];
	Vector2 m_Position;
	Vector2 m_Velocity;
	int m_Speed;
	SDL_Rect m_Bounds;
};

#endif

