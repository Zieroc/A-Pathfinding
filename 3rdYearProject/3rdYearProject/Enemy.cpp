#include "Enemy.h"

Enemy::Enemy()
{
	CalcBounds();
	m_MaxHealth = 15;
	m_CurrentHealth = 15;
	m_MaxAP = 8;
	m_CurrentAP = 8;
}

Enemy::Enemy(Vector2 position, int speed)
{
	m_Position = position;
	m_Speed = speed;
	CalcBounds();
	m_MaxHealth = 15;
	m_CurrentHealth = 15;
	m_MaxAP = 8;
	m_CurrentAP = 8;
}

Enemy::~Enemy()
{
}


void Enemy::Initialize(Sprite* sprites[], TileMap* map, PlayerManager* playerRef, SoundManager* soundMan)
{
	Character::Initialize(sprites, map, soundMan);
	m_p_PlayerRef = playerRef;
}

void Enemy::SetTarget(Vector2 target)
{
	m_Target = target;
	m_TargetPlayerPos = m_p_CurrentTargetPlayer->GetPosition();
	m_HasReachedTarget = false;
	m_HasPath = false;
}

void Enemy::Update(Uint32 timeElapsed, int turn)
{
	GameObject::Update(timeElapsed);
	
	if(turn == 2)
	{
		if(!m_HasPath)
		{
			if(m_p_PlayerRef != NULL)
			{

				if(!m_p_PlayerRef->GetPlayers().empty())
				{
					GetTargetPlayer();

					//If we are beside a player attack
					if(m_Position.DistanceTo(m_p_CurrentTargetPlayer->GetPosition()) == 32)
					{
						if(m_CurrentAP > 0)
						{
							SwitchAnimation(1);
							int attack = m_CurrentAP;
							m_CurrentAP = 0;
							for(int i = 0; i < m_p_PlayerRef->GetPlayers().size(); i++)
							{
								if(m_Position.DistanceTo(m_p_PlayerRef->GetPlayer(i)->GetPosition()) == 32)
								{
									m_p_PlayerRef->GetPlayer(i)->DecHealth(attack);
								}
							}
						}
					}
					else
					{
						SetTarget(m_p_CurrentTargetPlayer->GetPosition());
					}
				}
			}
		}

		Move(timeElapsed);

		if(!m_HasPath)
		{
			//If we don't have a path after moving set AP to 0
			//This usually means paths to the players are blocked by other enemies
			//Better to have enemy decided to do nothing than hang up the turn
			m_CurrentAP = 0;
		}
	}
	else
	{
		m_p_CurrentTargetPlayer = NULL;
		m_HasPath = false;
		while(m_p_Pathfinder->GetNextNode().x >= 0)
		{
		}
	}
}


void Enemy::GetPathNode()
{
	m_HasReachedTarget = true;

	m_Target = m_p_Pathfinder->GetNextNode();
	if(m_Target.x < 0 || m_Target == m_TargetPlayerPos)
	{
		m_HasPath = false;
		while(m_p_Pathfinder->GetNextNode().x >= 0)
		{
			//Run through the rest of the path if we still have any nodes left in it to remove them from the next run
		}
	}
	else
	{
		m_HasReachedTarget = false;
	}
}

void Enemy::GetTargetPlayer()
{
	//Target the closer player as the crow flies
	//Targets may not necessarily be the closet along the paths but as the enemy nears players this will become more accurate
	//Represents the enemies only knowng the generaly locale of the players rather than exact positions
	if(!m_p_PlayerRef->GetPlayers().empty())
	{
		float lowestDistance = m_Position.DistanceTo(m_p_PlayerRef->GetPlayer(0)->GetPosition());
		m_p_CurrentTargetPlayer = m_p_PlayerRef->GetPlayer(0);

		float distance;
		for(int i = 1; i < m_p_PlayerRef->GetPlayers().size(); i++)
		{
			distance = 	m_Position.DistanceTo(m_p_PlayerRef->GetPlayer(i)->GetPosition());

			if(distance < lowestDistance)
			{
				lowestDistance = distance;
				m_p_CurrentTargetPlayer = m_p_PlayerRef->GetPlayer(i);
			}
		}
	}
}