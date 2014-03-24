#ifndef ACTION_H
#define ACTION_H

#include <string>

class Action
{
public:
	Action();
	Action(std::string name, int cost, int type, int amount);
	~Action();
	std::string GetName();
	int GetCost();
	int GetType();
	int GetAmount();
private:
	std::string m_Name;
	int m_Cost; // AP cost of this action
	int m_Type; // 1 - Damage, 2 - Heal
	int m_Amount; //Amount of damage/healing done by this action
};

#endif
