#include "PhysicsComponent.h"
#include "GameObject.h"

PhysicsComponent::PhysicsComponent()
{
}

PhysicsComponent::~PhysicsComponent()
{
}

void PhysicsComponent::Initialize(TileMap* map, GameObject* gameObject)
{
	m_p_Map = map;
	m_Target = gameObject->GetPosition();
	m_HasReachedTarget = true;

	m_p_Pathfinder = new Pathfinder(map);
}

void PhysicsComponent::Update(GameObject* gameObject, Uint32 timeElapsed)
{
	//If we are at our target we don't need to move
	if(!m_HasReachedTarget)
	{
		if(!m_HasPath)
		{
			//If we haven't got a path and aren't at the target we need to calculate the path
			Vector2 start = gameObject->GetPosition();
			m_p_Pathfinder->FindPath(m_p_Map->GetTileAtPoint(start.x, start.y), m_p_Map->GetTileAtPoint(m_Target.x, m_Target.y));
			m_Target = m_p_Pathfinder->GetNextNode();
			m_HasPath = true;
		}

		
		Vector2 velocity(0, 0);

		Vector2 pos = gameObject->GetPosition();

		if(pos.x < m_Target.x)
		{
			velocity.x = std::min(gameObject->GetSpeed() * (timeElapsed / 1000.0f), m_Target.x - pos.x);
		}
		else if(pos.x > m_Target.x)
		{
			velocity.x = std::max(-gameObject->GetSpeed() * (timeElapsed / 1000.0f), m_Target.x - pos.x);
		}
		if(pos.y < m_Target.y)
		{
			velocity.y = std::min(gameObject->GetSpeed() * (timeElapsed / 1000.0f), m_Target.y - pos.y);
		}
		else if(pos.y > m_Target.y)
		{
			velocity.y = std::max(-gameObject->GetSpeed() * (timeElapsed / 1000.0f), m_Target.y - pos.y);
		}

		gameObject->SetVelocity(velocity);
		HorizontalTileCollisionTest(gameObject);
		VerticalTileCollisionTest(gameObject);

		pos += gameObject->GetVelocity();
		gameObject->SetPosition(pos);
		gameObject->CalcBounds();

	
		if(gameObject->GetPosition() == m_Target)
		{
			m_HasReachedTarget = true;

			m_Target = m_p_Pathfinder->GetNextNode();
			if(m_Target.x > 0)
			{
				m_HasReachedTarget = false;
			}
			else
			{
				gameObject->Send(1);
				m_HasPath = false;
			}
		}
	}
}

void PhysicsComponent::Receive(int message)
{
	DEBUG_MSG("PHYSICS COMPONENT MESSAGE RECIEVED: " + message);
}

void PhysicsComponent::SetTarget(Vector2 target)
{
	m_Target = target;
	m_HasReachedTarget = false;
	m_HasPath = false;
}

void PhysicsComponent::HorizontalTileCollisionTest(GameObject* gameObject)
{
	if(!gameObject->GetVelocity().x == 0) //If we aren't moving horizontally we can't collide with the map horizontally so only check if we have a horizontally velcoity
	{

		//Calculate the new position of the object if it moved at this amount
		SDL_Rect movedBounds(gameObject->GetBounds());
		movedBounds.x += gameObject->GetVelocity().x;

		Vector2 corner1, corner2; //The top and bottom corner or the left or right side depending on how we are moving 

		if(gameObject->GetVelocity().x < 0)
		{
			corner1.x = movedBounds.x;
			corner1.y = movedBounds.y + 1;

			corner2.x = movedBounds.x;
			corner2.y = movedBounds.y + movedBounds.h - 1;
		}
		else
		{
			corner1.x = movedBounds.x + movedBounds.w;
			corner1.y = movedBounds.y + 1;

			corner2.x = movedBounds.x + movedBounds.w;
			corner2.y = movedBounds.y + movedBounds.h - 1;
		}

		Vector2 mapCell1(m_p_Map->GetCellByPointX(floorf(corner1.x)), m_p_Map->GetCellByPointY(floorf(corner1.y))); //Get the Map cell that corner 1 is in
		Vector2 mapCell2(m_p_Map->GetCellByPointX(floorf(corner2.x)), m_p_Map->GetCellByPointY(floorf(corner2.y))); //Get the Map cell that corner 2 is in

		//If it will be an impassable cell then don't let the object move
		if (!m_p_Map->IsCellPassable(mapCell1.x, mapCell1.y) || !m_p_Map->IsCellPassable(mapCell2.x, mapCell2.y))
		{
			gameObject->SetVelocity(Vector2(0, gameObject->GetVelocity().y));
			//If we are colliding with a wall the target must be an impassable tile so send a warning message
			gameObject->Send(2);
			DEBUG_MSG("UNREACHABLE TARGET!");
			m_HasReachedTarget = true; //Target is unreachable stop trying to get to it
		}
	}
}

void PhysicsComponent::VerticalTileCollisionTest(GameObject* gameObject)
{
	if(!gameObject->GetVelocity().y == 0) //If we aren't moving vertically we can't collide with the map vertically so only check if we have a y velocity
	{
		//Calculate the new position of the object if it moved at this amount
		SDL_Rect movedBounds(gameObject->GetBounds());
		movedBounds.y += gameObject->GetVelocity().y;

		Vector2 corner1, corner2; //The left and right corner or the top or bottom side depending on how we are moving 

		if(gameObject->GetVelocity().y < 0)
		{
			corner1.x = movedBounds.x + 1;
			corner1.y = movedBounds.y;

			corner2.x = movedBounds.x + movedBounds.w - 1;
			corner2.y = movedBounds.y;
		}
		else
		{
			corner1.x = movedBounds.x + 1;
			corner1.y = movedBounds.y + movedBounds.h;

			corner2.x = movedBounds.x + movedBounds.w - 1;
			corner2.y = movedBounds.y + movedBounds.h;
		}

		Vector2 mapCell1(m_p_Map->GetCellByPointX(floorf(corner1.x)), m_p_Map->GetCellByPointY(floorf(corner1.y))); //Get the Map cell that corner 1 is in
		Vector2 mapCell2(m_p_Map->GetCellByPointX(floorf(corner2.x)), m_p_Map->GetCellByPointY(floorf(corner2.y))); //Get the Map cell that corner 2 is in

		//If it will be an impassable cell then don't let the object move
		if (!m_p_Map->IsCellPassable(mapCell1.x, mapCell1.y) || !m_p_Map->IsCellPassable(mapCell2.x, mapCell2.y))
		{
			gameObject->SetVelocity(Vector2(gameObject->GetVelocity().x, 0));
			//If we are colliding with a wall the target must be an impassable tile so send a warning message
			gameObject->Send(2);
			DEBUG_MSG("UNREACHABLE TARGET!");
			m_HasReachedTarget = true; //Target is unreachable stop trying to get to it
		}
	}
}