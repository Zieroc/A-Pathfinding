#include "Enemy.h"

Enemy::Enemy()
{
	CalcBounds();
}

Enemy::Enemy(Vector2 position, int speed)
{
	m_Position = position;
	m_Speed = speed;
	CalcBounds();
}

Enemy::~Enemy()
{
}


void Enemy::Initialize(Sprite* sprites[], TileMap* map, Character* playerRef)
{
	Character::Initialize(sprites, map);
	m_p_PlayerRef = playerRef;
}

void Enemy::SetTarget(Vector2 target)
{
	m_Target = target;
	m_TargetPlayerPos = target;
	m_HasReachedTarget = false;
	m_HasPath = false;
}

void Enemy::Update(Uint32 timeElapsed, int turn)
{
	GameObject::Update(timeElapsed);
	
	if(turn == 2)
	{
		if(m_p_PlayerRef != NULL)
		{
			if(!m_HasPath)
			{
				SetTarget(m_p_PlayerRef->GetPosition());
			}
		}
		Move(timeElapsed);
	}
}


void Enemy::GetPathNode()
{
	m_HasReachedTarget = true;

	m_Target = m_p_Pathfinder->GetNextNode();
	if(m_Target.x < 0 || m_Target == m_TargetPlayerPos)
	{
		m_HasPath = false;
	}
	else
	{
		m_HasReachedTarget = false;
	}
}