#include "Potion.h"



Potion::Potion() : m_name("Health Potion"), m_description("increase hp"), m_potency("500"), m_cost("100")
{

}

Potion::Potion(cString name, cString description, cString potency, cString cost) : m_name(name), m_description(description), m_potency(potency), m_cost(cost)
{
}

Potion::Potion(const Potion & potion)
{
	m_cost = potion.m_cost;
	m_description = potion.m_description;
	m_name = potion.m_name;
	m_potency = potion.m_potency;
}

Potion & Potion::operator=(const Potion & potion)
{
	if (this != &potion)
	{
		m_name = potion.m_name;
		m_description = potion.m_description;
		m_potency = potion.m_potency;
		m_cost = potion.m_cost;
	}

	return *this;
}

void Potion::setName(cString name)
{
	m_name = name;
}

cString Potion::getName() const
{
	return m_name;
}

void Potion::setDescription(cString description)
{
	m_description = description;
}

cString Potion::getDescription() const
{
	return m_description;
}

void Potion::setPotency(cString potency)
{
	m_potency = potency++;
}

cString Potion::getPotency() const
{
	return m_potency;
}

void Potion::setCost(int cost)
{
	int copper = 0;
	int silver = 0;
	int gold = 0;
	int platinum = 0;
	char charCopper[200];
	char charSilver[200];
	char charGold[200];
	char charPlatinum[200];
	char totalCost[5000];

	if ((cost / 1000) > 0)
	{
		platinum = cost / 1000;
		cost = cost % 1000;
	}
	if ((cost / 100) > 0)
	{
		gold = cost / 100;
		cost = cost % 100;
	}
	if ((cost / 10) > 0)
	{
		silver = cost / 10;
		cost = cost % 10;
	}
	copper = cost;

	_itoa(platinum, charPlatinum, 10);
	_itoa(gold, charGold, 10);
	_itoa(silver, charSilver, 10);
	_itoa(copper, charCopper, 10);

	strcpy(totalCost, charPlatinum);
	strcat(totalCost, ".");
	strcat(totalCost, charGold);
	strcat(totalCost, ".");
	strcat(totalCost, charSilver);
	strcat(totalCost, ".");
	strcat(totalCost, charCopper);

	m_cost = totalCost;

}

void Potion::setCost(cString cost)
{
	m_cost = cost;
}

cString Potion::getCost() const
{
	return m_cost;
}

void Potion::display()
{
	cout << "Name: " << m_name << endl;
	cout << "Description: " << m_description << endl;
	cout << "Potency: " << m_potency << endl;
	cout << "Cost: " << m_cost << endl;
}

bool Potion::operator==(const Potion & rhs) const
{
	bool test = false;
	if (m_name == rhs.m_name)
	{
		test = true;
	}

	return test;
}

bool Potion::operator<(const Potion & rhs) const
{
	bool test = false;
	if (m_name < rhs.m_name)
	{
		test = true;
	}

	return test;
}

bool Potion::operator>(const Potion & rhs) const
{
	bool test = false;
	if (m_name > rhs.m_name)
	{
		test = true;
	}

	return test;
}

bool Potion::operator<=(const Potion & rhs) const
{
	bool test = false;
	if (m_name <= rhs.m_name)
	{
		test = true;
	}

	return test;
}

bool Potion::operator>=(const Potion & rhs) const
{
	bool test = false;
	if (m_name >= rhs.m_name)
	{
		test = true;
	}

	return test;
}

bool Potion::operator!=(const Potion & rhs) const
{
	bool test = false;
	if (m_name != rhs.m_name)
	{
		test = true;
	}

	return test;
}

int Potion::usePotion()
{
	return 500;
}

Potion::~Potion()
{
}
