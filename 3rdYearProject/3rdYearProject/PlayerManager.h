#ifndef PLAYER_MANAGER_H
#define PLAYER_MANAGER_H

#include "Character.h"

class PlayerManager
{
public:
	PlayerManager();
	~PlayerManager();
	void Update(Uint32 timeElapsed, int turn);
	void Draw(SDL_Renderer* renderer, Camera* camera);
	void AddPlayer(Character* player);
	Character* GetPlayer(int i);
	void RemovePlayer(int i);
	void FillAP();
private:
	std::vector<Character*> m_p_Players;
};

#endif