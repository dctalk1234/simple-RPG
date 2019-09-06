#pragma once
#include "Monster.h"
class SecondaryEnemy : public Monster
{
public:
	SecondaryEnemy();
	SecondaryEnemy(const SecondaryEnemy& data);
	SecondaryEnemy& operator=(SecondaryEnemy& rhs);
	~SecondaryEnemy();
};

