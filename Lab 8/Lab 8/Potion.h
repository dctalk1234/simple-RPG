#pragma once
#include "cString.h"


class Potion
{
public:
	Potion();
	Potion(cString name, cString description, cString potency, cString cost);
	Potion(const Potion& potion);
	Potion& operator=(const Potion& potion);
	void setName(cString name);
	cString getName() const;
	void setDescription(cString description);
	cString getDescription() const;
	void setPotency(cString potency);
	cString getPotency() const;
	void setCost(int cost);
	void setCost(cString cost);
	cString getCost() const;
	void display();
	bool operator==(const Potion& rhs) const;
	bool operator<(const Potion& rhs) const;
	bool operator>(const Potion& rhs) const;
	bool operator<=(const Potion& rhs) const;
	bool operator>=(const Potion& rhs) const;
	bool operator!=(const Potion& rhs) const;
	int usePotion();
	~Potion();
private:
	cString m_name;
	cString m_description;
	cString m_potency;
	cString m_cost;
};

