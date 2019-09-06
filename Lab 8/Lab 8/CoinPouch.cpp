#include "CoinPouch.h"



CoinPouch::CoinPouch() : m_coins(0)
{
}

CoinPouch::CoinPouch(const CoinPouch & pouch) : m_coins(0)
{
	m_coins = pouch.m_coins;
}

CoinPouch & CoinPouch::operator=(const CoinPouch & pouch)
{
	if (this != &pouch)
	{
		m_coins = pouch.m_coins;
	}

	return *this;
}

void CoinPouch::addCoins(int x)
{
	m_coins += x;
}

void CoinPouch::subtCoins(int x)
{
	m_coins -= x;
}

int CoinPouch::getCoins()
{
	return m_coins;
}

void CoinPouch::display()
{
	cout << m_coins << endl;
}

CoinPouch::~CoinPouch()
{
}
