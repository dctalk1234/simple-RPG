#include "SecondaryEnemy.h"



SecondaryEnemy::SecondaryEnemy() : Monster("Wargul", 200, 20, 50)
{
}

SecondaryEnemy::SecondaryEnemy(const SecondaryEnemy & data) : Monster(data.m_name, data.m_hp, data.m_attack, 0)
{
}

SecondaryEnemy & SecondaryEnemy::operator=(SecondaryEnemy & rhs)
{
	if (this != &rhs)
	{
		m_name = rhs.m_name;
		m_hp = rhs.m_hp;
		m_attack = rhs.m_attack;
		m_shield = 0;
	}
	
	return *this;
}


SecondaryEnemy::~SecondaryEnemy()
{
}
