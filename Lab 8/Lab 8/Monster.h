#pragma once
#include "cString.h"
class Monster
{
public:
	Monster();
	Monster(const Monster& data);
	Monster& operator=(Monster& rhs);
	Monster(cString name, int hp, int attack, int shield);
	virtual int attack();
	void takeDamage(int damage);
	int getHP();
	virtual ~Monster() = 0;
	void display();

protected:
	cString m_name;
	int m_hp;
	int m_attack;
	int m_shield;
};

