#pragma once
#include "Monster.h"
class Boss : public Monster
{
public:
	Boss(int level);
	Boss(const Boss& boss);
	Boss& operator=(Boss& rhs);
	int attack();
	~Boss();

private:
	int m_specialAttack;
};

