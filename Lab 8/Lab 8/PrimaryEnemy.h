#pragma once
#include "Monster.h"
class PrimaryEnemy : public Monster
{
public:
	PrimaryEnemy();
	PrimaryEnemy(const PrimaryEnemy& data);
	PrimaryEnemy& operator=(PrimaryEnemy& rhs);
	~PrimaryEnemy();

};

