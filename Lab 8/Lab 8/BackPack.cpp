#include "BackPack.h"



BackPack::BackPack() : m_potionsArr()
{
}

BackPack::BackPack(const BackPack & pack) : m_potionsArr(pack.m_potionsArr)
{
}

BackPack::BackPack(const list<Potion> & arr) : m_potionsArr(arr)
{
}

BackPack & BackPack::operator=(const BackPack & pack)
{
	if (this != &pack)
	{
		m_potionsArr = pack.m_potionsArr;
	}
	return *this;
}

list<Potion> & BackPack::getPotionArr()
{
	return m_potionsArr;
}

void BackPack::display()
{
	m_potionsArr.display();
}


BackPack::~BackPack()
{
}
