#include "Action.h"


Action::Action() : m_Name("ACTION"), m_Cost(1), m_Type(1), m_Amount(1)
{
}

Action::Action(std::string name, int cost, int type, int amount)
{
	m_Name = name;
	m_Cost = cost;
	m_Type = type;
	m_Amount = amount;
}


Action::~Action()
{
}

std::string Action::GetName()
{
	return m_Name;
}

int Action::GetCost()
{
	return m_Cost;
}

int Action::GetType()
{
	return m_Type;
}

int Action::GetAmount()
{
	return m_Amount;
}
