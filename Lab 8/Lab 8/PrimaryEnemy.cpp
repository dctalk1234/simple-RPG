#include "PrimaryEnemy.h"



PrimaryEnemy::PrimaryEnemy() : Monster("Kourana",100,10,0)
{
}

PrimaryEnemy::PrimaryEnemy(const PrimaryEnemy & data): Monster(data)
{
}

PrimaryEnemy & PrimaryEnemy::operator=(PrimaryEnemy & rhs)
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


PrimaryEnemy::~PrimaryEnemy()
{
}
