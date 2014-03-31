#ifndef PLAYER_MANAGER_H
#define PLAYER_MANAGER_H

#include "InputHandler.h"
#include "Character.h"

class PlayerManager
{
public:
	PlayerManager();
	~PlayerManager();
	void Update(Uint32 timeElapsed, int turn);
	void Draw(SDL_Renderer* renderer, Camera* camera);
	Character* HandleInput(InputHandler* input, Camera* camera);
	void AddPlayer(Character* player);
	Character* GetPlayer(int i);
	void RemovePlayer(int i);
	void FillAP();
	std::vector<Character*> GetPlayers();
private:
	std::vector<Character*> m_p_Players;
	bool m_Clicked;
};

#endif