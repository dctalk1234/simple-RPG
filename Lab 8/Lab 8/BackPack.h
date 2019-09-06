#pragma once
#include "list.h"
/*
This is a backpack for an rpg character which includes a linked list of potions.
*/

class BackPack
{
public:
	BackPack();
	BackPack(const BackPack& pack);
	BackPack(const list<Potion>& arr);
	BackPack& operator=(const BackPack& pack);
	list<Potion>& getPotionArr();
	void display();
	~BackPack();

private:
	list<Potion> m_potionsArr;
};
