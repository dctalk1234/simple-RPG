#pragma once
#include "BackPack.h"
#include "CoinPouch.h"
class Character 
{
public:
	Character();
	Character(const Character& character);
	Character& operator=(const Character& character);
	void display();
	void setName(cString name);
	cString getName();
	void setPack(BackPack pack);
	BackPack& getPack();
	void setPouch(CoinPouch pouch);
	CoinPouch& getPouch();
	int normalStrike();
	int block();
	int berserk();
	int getHP();
	void setHP(int hp);
	void increaseHP(int hp);
	int getArmor();
	void setArmor(int armor);
	void increaseArmor(int armor);
	int getRange();
	void setRange(int range);
	void nextLevel();
	int getlevel();
	void setLevel(int level);
	void takeDamage(int damage);
	void increaseAttack(int increase);
	void setAttack(int attack);
	int getAttack();
	~Character();
private:
	cString m_name;
	BackPack m_pack;
	CoinPouch m_pouch;
	int m_hp;
	int m_armor;
	int m_Range;
	int m_currentLevel;
	int m_attack;
};

