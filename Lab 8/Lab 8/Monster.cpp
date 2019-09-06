#include "Monster.h"



Monster::Monster(): m_attack(0), m_hp(0), m_name("default"), m_shield(0)
{
}

Monster::Monster(const Monster & data) : m_attack(data.m_attack), m_hp(data.m_hp), m_name(data.m_name), m_shield(data.m_shield)
{
}

Monster & Monster::operator=(Monster & rhs)
{
	if (this != &rhs)
	{
		m_attack = rhs.m_attack;
		m_hp = rhs.m_hp;
		m_name = rhs.m_name;
		m_shield = rhs.m_shield;
	}
	
	return *this;
}

Monster::Monster(cString name, int hp, int attack, int shield) : m_name(name), m_hp(hp), m_attack(attack), m_shield(shield)
{
}

int Monster::attack()
{
	return m_attack;
}

void Monster::takeDamage(int damage)
{
	if (damage < m_shield)
	{
		m_shield -= damage;
	}
	else if (damage >= m_shield && (damage - m_shield) < m_hp)
	{
		damage -= m_shield;
		m_shield -= m_shield;
		m_hp -= damage;
	}
	else if (damage > m_shield && (damage - m_shield) >= m_hp)
	{
		m_hp -= m_hp;
	}
}

int Monster::getHP()
{
	return m_hp;
}

Monster::~Monster()
{
}

void Monster::display()
{
	cout << "Monst Name: " << m_name << " HP Remaining: " << m_hp << " Shield Remaining: " << m_shield << endl;
}
