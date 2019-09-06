#pragma once
#include <iostream>
using std::cout;
using std::endl;

class CoinPouch
{
public:
	CoinPouch();
	CoinPouch(const CoinPouch& pouch);
	CoinPouch& operator=(const CoinPouch& pouch);
	void addCoins(int x);
	void subtCoins(int x);
	int getCoins();
	void display();
	~CoinPouch();
private:
	int m_coins;
};