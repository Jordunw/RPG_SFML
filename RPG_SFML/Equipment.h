#pragma once
#include <vector>
#include <iostream>

class Weapon {
protected:
	std::string name;
	int owned;
	int equipped;
	bool two_handed;
	double damage_multi;
	double sell_price;
	std::vector<bool> can_equip; // [0] fighter [1] rogue [2] wizard [3] barbarian [4] catgirl
	std::vector<bool> effects;
	std::string description;

public:
	std::string getName() { return name; }
	int numOwned() { return owned; }
	int numEquipped() { return equipped; }
	bool twoHanded() { return two_handed; }
	double damageMulti() { return damage_multi; }
	double sellPrice() { return sell_price; }
	std::vector<bool> canEquip() { return can_equip; }
	std::vector<bool> getEffects() { return effects; }
	std::string getDescription() { return description; }

	void addOwned(int x = 1) { owned += x; }
	void subtractOwned(int x = 1) { owned -= x; }
	void addEquipped() { equipped += 1; }
	void subtractEquipped() { equipped -= 1; }

	virtual int getLegendary() { return -1; }

	Weapon() {}

	Weapon(std::string name, std::vector<bool> can_equip, bool two_handed, double damage_multi,
		double sell_price, std::vector<bool> effects, std::string description)
		:
		name{ name },
		owned{ 0 },
		equipped{ 0 },
		can_equip{ can_equip },
		two_handed{ two_handed },
		damage_multi{ damage_multi },
		sell_price{ sell_price },
		effects{ effects },
		description{ description }{}
	~Weapon() {}
};

class Legendary : public Weapon {
protected:
	int legendary;
public:
	virtual int getLegendary() override { return legendary; }

	Legendary(std::string name, bool two_handed, double damage_multi,
		double sell_price, std::vector<bool> effects, std::string description, int legendary, int owned = 0, int equipped = 0)
		: legendary{ legendary } {
		this->name = name;
		this->can_equip = { true, true, true, true, true };
		this->two_handed = two_handed;
		this->damage_multi = damage_multi;
		this->sell_price = sell_price;
		this->effects = effects;
		this->description = description;
		this->owned = owned;
		this->equipped = equipped;
	}

	virtual ~Legendary() {}
};

class Armor {
	std::string name;
	int owned;
	bool equipped;
	double protection_multi;
	// [0] - Thrust
	// [1] - Slash
	// [2] - Blunt force
	std::vector<bool> weakness;
	double sell_price;
	std::string description;
public:
	std::string getName() { return name; }
	int numOwned() { return owned; }
	bool getEquipped() { return equipped; }
	double protMulti() { return protection_multi; }
	double sellPrice() { return sell_price; }
	std::string getDescription() { return description; }

	void addOwned(int x = 1) { owned += x; }
	void subtractOwned(int x = 1) { owned -= x; }
	void equip() { equipped = true; }
	void unequip() { equipped = false; }

	Armor(){}
	Armor(std::string name, double protection_multi, double sell_price, std::string description, std::vector<bool> weakness) :
		name{ name }, owned{ 0 }, equipped{ false }, weakness{ weakness }, protection_multi{ protection_multi }, sell_price{ sell_price }, description{ description }{}
	~Armor() {}
};