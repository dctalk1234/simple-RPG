#include "Character.h"



Character::Character() : m_name("null"), m_pack(), m_pouch(), m_hp(rand() % 2000 + 2000), m_armor(rand() % 1000), m_Range(rand() % 20), m_currentLevel(1), m_attack(150)
{
}

Character::Character(const Character & character) : m_name(character.m_name), m_pack(character.m_pack), m_pouch(character.m_pouch), m_hp(character.m_hp), m_armor(character.m_armor), m_Range(character.m_Range), m_currentLevel(character.m_currentLevel), m_attack(character.m_attack)
{
}

Character & Character::operator=(const Character & character)
{
	if (this != &character)
	{
		m_name = character.m_name;
		m_pack = character.m_pack;
		m_pouch = character.m_pouch;
		m_hp = character.m_hp;
		m_Range = character.m_Range;
		m_armor = character.m_armor;
		m_currentLevel = character.m_currentLevel;
		m_attack = character.m_attack;
	}

	return *this;
}

void Character::display()
{
	cout << "Name: ";
	m_name.display();
	cout << endl;

	cout << "BackPack: ";
	m_pack.display();
	cout << endl;

	cout << "Coin Pouch: ";
	m_pouch.display();
	cout << endl;

	cout << "HP: ";
	cout << m_hp;
	cout << endl;

	cout << "Armor: ";
	cout << m_armor;
	cout << endl;

	cout << "Range: ";
	cout << m_Range;
	cout << endl;

	cout << "Current Level: " << endl;
	cout << m_currentLevel;
	cout << endl;
}

void Character::setName(cString name)
{
	m_name = name;
}

cString Character::getName()
{
	return m_name;
}

void Character::setPack(BackPack pack)
{
	m_pack = pack;
}

BackPack& Character::getPack()
{
	return m_pack;
}

void Character::setPouch(CoinPouch pouch)
{
	m_pouch = pouch;
}

CoinPouch& Character::getPouch()
{
	return m_pouch;
}

int Character::normalStrike()
{
	return m_attack;
}

int Character::block()
{
	m_armor += (.25 * m_armor);
	return (.5 * m_attack);
}

int Character::berserk()
{
	if (m_armor > 50)
	{
		m_armor -= (.02 * m_armor);
	}
	else
	{
		int subt = (.02 * m_armor);
		subt -= m_armor;
		m_armor -= m_armor;
		m_hp -= subt;
	}
	return (2.5 * m_attack);
}

int Character::getHP()
{
	return m_hp;
}

void Character::setHP(int hp)
{
	m_hp = hp;
}

void Character::increaseHP(int hp)
{
	m_hp += hp;
}

int Character::getArmor()
{
	return m_armor;
}

void Character::setArmor(int armor)
{
	m_armor = armor;
}

void Character::increaseArmor(int armor)
{
	m_armor += armor;
}

int Character::getRange()
{
	return m_Range;
}

void Character::setRange(int range)
{
	m_Range = range;
}

/*
	increment which level the character is on.
*/
void Character::nextLevel()
{
	m_currentLevel++;
}

int Character::getlevel()
{
	return m_currentLevel;
}

void Character::setLevel(int level)
{
	m_currentLevel = level;
}

void Character::takeDamage(int damage)
{
	if (damage <= m_armor)
	{
		m_armor -= damage;
	}
	else if (damage > m_armor && (damage-m_armor) < m_hp)
	{
		damage -= m_armor;
		m_armor -= m_armor;
		m_hp -= damage;
	}
	else if (damage > m_armor && (damage - m_armor) >= m_hp)
	{
		m_hp -= m_hp;
	}
}

void Character::increaseAttack(int increase)
{
	m_attack += increase;
}

void Character::setAttack(int attack)
{
	m_attack = attack;
}

int Character::getAttack()
{
	return m_attack;
}


Character::~Character()
{
}
