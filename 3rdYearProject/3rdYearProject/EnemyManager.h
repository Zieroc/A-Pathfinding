#ifndef ENEMY_MANAGER_H
#define ENEMY_MANAGER_H

#include "Enemy.h"
#include <vector>

class EnemyManager
{
public:
	EnemyManager();
	~EnemyManager();
	void Update(Uint32 timeElapsed, int turn);
	void Draw(SDL_Renderer* renderer, Camera* camera);
	void AddEnemy(Enemy* enemy);
	Enemy* GetEnemy(int i);
	void RemoveEnemy(int i);
	void FillAP();
private:
	std::vector<Enemy*> m_p_Enemies;
};

#endif