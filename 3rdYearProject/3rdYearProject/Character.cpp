#include "Character.h"

Character::Character() : m_MaxAP(10), m_CurrentAP(10), m_HasPath(false), m_HasReachedTarget(false), m_MaxHealth(20), m_CurrentHealth(20)
{
	CalcBounds();
}

Character::Character(Vector2 position, int speed): m_MaxAP(10), m_CurrentAP(10), m_HasPath(false), m_HasReachedTarget(false), m_MaxHealth(20), m_CurrentHealth(20)
{
	m_Position = position;
	m_Speed = speed;
	CalcBounds();
}

Character::~Character()
{
}

void Character::Initialize(Sprite* sprites[], TileMap* map, SoundManager* soundMan)
{
	GameObject::Initialize(sprites);

	m_p_SoundManager = soundMan;

	m_p_Map = map;
	m_p_Map->GetTileAtPoint(m_Position.x, m_Position.y)->SetOccupied(true);
	m_Target = GetPosition();
	m_HasReachedTarget = true;

	m_p_Pathfinder = new Pathfinder(map);
}

void Character::Update(Uint32 timeElapsed, int turn)
{
	GameObject::Update(timeElapsed);
	
	if(turn == 1)
	{
		Move(timeElapsed);
	}
}

void Character::SetTarget(Vector2 target)
{
	if(!(((int)target.x / TileMap::TILE_WIDTH == (int)m_Position.x / TileMap::TILE_WIDTH) && ((int)target.y / TileMap::TILE_HEIGHT == (int)m_Position.y / TileMap::TILE_HEIGHT)))
	{
		m_Target = target;
		m_HasReachedTarget = false;
		m_HasPath = false;
	}
}

void Character::Move(Uint32 timeElapsed)
{
	if(!m_HasReachedTarget)
	{
		if(m_CurrentAP > 0)
		{
			if(!m_HasPath)
			{
				//If we haven't got a path and aren't at the target we need to calculate the path
				Vector2 start = GetPosition();
				m_HasPath = m_p_Pathfinder->FindPath(m_p_Map->GetTileAtPoint(start.x, start.y), m_p_Map->GetTileAtPoint(m_Target.x, m_Target.y));
				GetPathNode();
			}

			if(m_HasPath)
			{
				if(m_p_Map->GetTileAtPoint(m_Position.x, m_Position.y)->GetOccupied())
				{
					m_p_Map->GetTileAtPoint(m_Position.x, m_Position.y)->SetOccupied(false);
				}

				Vector2 velocity(0, 0);

				Vector2 pos = GetPosition();

				if(pos.x < m_Target.x)
				{
					velocity.x = std::min(GetSpeed() * (timeElapsed / 1000.0f), m_Target.x - pos.x);
				}
				else if(pos.x > m_Target.x)
				{
					velocity.x = std::max(-GetSpeed() * (timeElapsed / 1000.0f), m_Target.x - pos.x);
				}
				if(pos.y < m_Target.y)
				{
					velocity.y = std::min(GetSpeed() * (timeElapsed / 1000.0f), m_Target.y - pos.y);
				}
				else if(pos.y > m_Target.y)
				{
					velocity.y = std::max(-GetSpeed() * (timeElapsed / 1000.0f), m_Target.y - pos.y);
				}

				SetVelocity(velocity);
				HorizontalTileCollisionTest();
				VerticalTileCollisionTest();

				pos += GetVelocity();
				SetPosition(pos);
				CalcBounds();

				if(GetPosition() == m_Target)
				{
					m_CurrentAP--;
					GetPathNode();
					m_p_Map->GetTileAtPoint(m_Position.x, m_Position.y)->SetOccupied(true);
				}
			}
		}
		else
		{
			//NO AP SO STOP MOVING
			m_HasReachedTarget = true;
			m_HasPath = false;
			while(m_p_Pathfinder->GetNextNode().x >= 0)
			{
			}
		}
	}
}

void Character::FillAP()
{
	m_CurrentAP = m_MaxAP;
}

void Character::DecreaseAP(int amount)
{
	m_CurrentAP -= amount;
}

void Character::FillHealth()
{
	m_CurrentHealth = m_MaxHealth;
}

void Character::IncHealth(int amount)
{
	m_CurrentHealth = amount;

	if(m_CurrentHealth > m_MaxHealth)
	{
		m_CurrentHealth = m_MaxHealth;
	}
}

void Character::DecHealth(int amount)
{
	m_p_SoundManager->PlaySoundEffect("hit.wav");
	m_CurrentHealth -= amount;
}

int Character::GetCurrentAP()
{
	return m_CurrentAP;
}

int Character::GetMaxAP()
{
	return m_MaxAP;
}

int Character::GetCurrentHealth()
{
	return m_CurrentHealth;
}

int Character::GetMaxHealth()
{
	return m_MaxHealth;
}

void Character::UnoccupyMap()
{
	m_p_Map->GetTileAtPoint(m_Position.x, m_Position.y)->SetOccupied(false);
}

void Character::GetPathNode()
{
	m_HasReachedTarget = true;

	m_Target = m_p_Pathfinder->GetNextNode();
	if(m_Target.x > 0)
	{
		m_HasReachedTarget = false;
	}
	else
	{
		m_HasPath = false;
	}
}

void Character::HorizontalTileCollisionTest()
{
	if(!GetVelocity().x == 0) //If we aren't moving horizontally we can't collide with the map horizontally so only check if we have a horizontally velcoity
	{
		//Calculate the new position of the object if it moved at this amount
		SDL_Rect movedBounds(GetBounds());
		movedBounds.x += GetVelocity().x;

		Vector2 corner1, corner2; //The top and bottom corner or the left or right side depending on how we are moving 

		if(GetVelocity().x < 0)
		{
			corner1.x = movedBounds.x + 1;
			corner1.y = movedBounds.y + 1;

			corner2.x = movedBounds.x + 1;
			corner2.y = movedBounds.y + movedBounds.h - 1;
		}
		else
		{
			corner1.x = movedBounds.x + movedBounds.w - 1;
			corner1.y = movedBounds.y + 1;

			corner2.x = movedBounds.x + movedBounds.w - 1;
			corner2.y = movedBounds.y + movedBounds.h - 1;
		}

		Vector2 mapCell1(m_p_Map->GetCellByPointX(floorf(corner1.x)), m_p_Map->GetCellByPointY(floorf(corner1.y))); //Get the Map cell that corner 1 is in
		Vector2 mapCell2(m_p_Map->GetCellByPointX(floorf(corner2.x)), m_p_Map->GetCellByPointY(floorf(corner2.y))); //Get the Map cell that corner 2 is in

		//If it will be an impassable cell then don't let the object move
		if (!m_p_Map->IsCellPassable(mapCell1.x, mapCell1.y) || !m_p_Map->IsCellPassable(mapCell2.x, mapCell2.y))
		{
			SetVelocity(Vector2(0, GetVelocity().y));
			DEBUG_MSG("UNREACHABLE TARGET!");
			m_HasReachedTarget = true; //Target is unreachable stop trying to get to it
		}
	}
}

void Character::VerticalTileCollisionTest()
{
	if(!GetVelocity().y == 0) //If we aren't moving vertically we can't collide with the map vertically so only check if we have a y velocity
	{
		//Calculate the new position of the object if it moved at this amount
		SDL_Rect movedBounds(GetBounds());
		movedBounds.y += GetVelocity().y;

		Vector2 corner1, corner2; //The left and right corner or the top or bottom side depending on how we are moving 

		if(GetVelocity().y < 0)
		{
			corner1.x = movedBounds.x + 1;
			corner1.y = movedBounds.y + 1;

			corner2.x = movedBounds.x + movedBounds.w - 1;
			corner2.y = movedBounds.y + 1;
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
			SetVelocity(Vector2(GetVelocity().x, 0));
			//If we are colliding with a wall the target must be an impassable tile so send a warning message
			DEBUG_MSG("UNREACHABLE TARGET!");
			m_HasReachedTarget = true; //Target is unreachable stop trying to get to it
		}
	}
}

