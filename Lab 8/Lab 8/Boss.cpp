#include "Boss.h"


Boss::Boss(int level) : Monster("", 0,0,0), m_specialAttack(0)
{
	switch (level)
	{
	case 1:
		m_name = "Myrddraal";
		m_hp = 1200;
		m_attack = 200;
		m_shield = 175;
		m_specialAttack = 400;
		break;
		
	case 2:
		m_name = "Asmodean";
		m_hp = 2400;
		m_attack = 300;
		m_shield = 175;
		m_specialAttack = 500;
		break;
	case 3:
		m_name = "Jumara";
		m_hp = 2800;
		m_attack = 400;
		m_shield = 175;
		m_specialAttack = 600;
		break;
	case 4:
		m_name = "Moghedien";
		m_hp = 3200;
		m_attack = 500;
		m_shield = 175;
		m_specialAttack = 700;
		break;
	case 5:
		m_name = "Ishmael";
		m_hp = 3600;
		m_attack = 600;
		m_shield = 175;
		m_specialAttack = 800;
		break;
	case 6:
		m_name = "Darkhound";
		m_hp = 4000;
		m_attack = 700;
		m_shield = 175;
		m_specialAttack = 900;
		break;
	case 7:
		m_name = "Dreadlord";
		m_hp = 4400;
		m_attack = 800;
		m_shield = 175;
		m_specialAttack = 1000;
		break;
	case 8:
		m_name = "Gray Man";
		m_hp = 4600;
		m_attack = 900;
		m_shield = 175;
		m_specialAttack = 1100;
		break;
	case 9:
		m_name = "Speaker for the Dark One";
		m_hp = 5000;
		m_attack = 1000;
		m_shield = 175;
		m_specialAttack = 1200;
		break;
	case 10:
		m_name = "The Dark One";
		m_hp = 7000;
		m_attack = 1100;
		m_shield = 175;
		m_specialAttack = 1300;
		break;
	}
}

Boss::Boss(const Boss & boss)
{
	m_attack = boss.m_attack;
	m_hp = boss.m_hp;
	m_name = boss.m_name;
	m_shield = boss.m_shield;
	m_specialAttack = boss.m_specialAttack;
}

Boss & Boss::operator=(Boss & rhs)
{
	if (this != &rhs)
	{
		m_attack = rhs.m_attack;
		m_hp = rhs.m_hp;
		m_name = rhs.m_name;
		m_shield = rhs.m_shield;
		m_specialAttack = rhs.m_specialAttack;
	}

	return *this;
}

int Boss::attack()
{
	static int numAttacks = 0;
	int attack = 0;
	if (numAttacks % 3 == 0)
	{
		attack = m_specialAttack;
	}
	else
	{
		attack = m_attack;
	}
	numAttacks++;

	return attack;
}

Boss::~Boss()
{
}
