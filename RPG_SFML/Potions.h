#pragma once
#include <vector>
#include <iostream>

class Potion {
protected:
	std::string name;
	int owned;
	double sell_price;
	double effect; // decimal value representing % (.35 -> 35%)
	int tier;
	std::string description;
public:
	std::string getName() { return name; }
	int numOwned() { return owned; }
	double sellPrice() { return sell_price; }
	double getEffect() { return effect; }
	std::string getDescription() { return description; }

	void subtract(int x = 1) { owned -= x; }
	void add(int x = 1) { owned += x; }

	Potion() {}

	Potion(std::string name, double sell_price, std::string description, double effect, int tier, int owned = 0)
		: name{ name }, sell_price{ sell_price }, description{ description }, effect{ effect }, tier{ tier }, owned{ owned }{}

	~Potion() {}
};

class HealthPotion : public Potion {
public:
	HealthPotion(std::string name, double sell_price, double effect, int tier, std::string description, int owned = 0) {
		this->name = name;
		this->sell_price = sell_price;
		this->effect = effect;
		this->tier = tier;
		this->description = description;
		this->owned = owned;
	}
};

class RegenerationPotion : public Potion {
public:
	RegenerationPotion(std::string name, double sell_price, double effect, int tier, std::string description, int owned = 0) {
		this->name = name;
		this->sell_price = sell_price;
		this->effect = effect;
		this->tier = tier;
		this->description = description;
		this->owned = owned;
	}
};

class StrengthPotion : public Potion {
public:
	StrengthPotion(std::string name, double sell_price, double effect, int tier, std::string description, int owned = 0) {
		this->name = name;
		this->sell_price = sell_price;
		this->effect = effect;
		this->tier = tier;
		this->description = description;
		this->owned = owned;
	}
};

class DefensePotion : public Potion {
public:
	DefensePotion(std::string name, double sell_price, double effect, int tier, std::string description, int owned = 0) {
		this->name = name;
		this->sell_price = sell_price;
		this->effect = effect;
		this->tier = tier;
		this->description = description;
		this->owned = owned;
	}
};

class InvisibilityPotion : public Potion {
public:
	InvisibilityPotion(std::string name, double sell_price, double effect, std::string description, int owned = 0, int tier = 1) {
		this->name = name;
		this->sell_price = sell_price;
		this->effect = effect;
		this->tier = tier;
		this->description = description;
		this->owned = owned;
	}
};