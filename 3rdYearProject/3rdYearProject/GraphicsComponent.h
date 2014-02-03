#ifndef GRAPHICS_COMPONENT_H
#define GRAPHICS_COMPONENT_H

#include "Component.h"
#include "Sprite.h"
#include <SDL.h>

class GameObject; //Forward Declaration

#define MAX_SPRITE 1

class GraphicsComponent : public Component
{
public:
	GraphicsComponent();
	virtual ~GraphicsComponent();
	virtual void Initialize(Sprite* sprites[], GameObject* gameObject);
	virtual void Update(Uint32 timeElapsed);
	virtual void Draw(GameObject* gameObject, SDL_Renderer* renderer, Camera* camera);
	virtual void Receive(int message);
protected:
	Sprite* m_p_Sprites[MAX_SPRITE];
	Sprite* m_p_CurrentSprite;
};

#endif