#pragma once
#include <string>
#include <iostream>
#include "Variables.h"
#include "Equipment.h"
#include "Potions.h"
#include "Sprite.h"
#include "Enum.h"

class Player {
protected:
	std::string class_name;
	std::string name;
	int x;
	int y;
	double health;
	double xp;
	int level;
	int inv_slots;
	double balance;
	// This vector defines basic player stats
	// [0] damage
	// [1] base health
	// [2] dexterity
	// [3] accuracy
	std::vector<double> stats;

	// This vector defines the number of turns left for temporary buffs or debuffs to stats - default is 3 turns
	// [0] poisoned			-- takes damage per turn
	// [1] healing			-- healing over multiple turns
	// [2] strengthened		-- increases attack
	// [3] shielded			-- increases defense
	// [4] weakened			-- decreases attack
	// [5] frightened		-- cannot attack (can use items)
	// [6] quicker			-- higher dex
	// [7] slower			-- lower dex
	// [8] stunned			-- skips turn
	std::vector<int> status_turns;

	// This vector defines the strength of status effects (+/-)
	// [0] healing
	// [1] strengthened
	// [2] resistance
	// [3] dexterity
	std::vector<int> status_val;

	std::vector<Weapon> weapons;
	std::vector<Armor> armor;
	std::vector<Potion> potions;
	// Add other items here

public:
	Sprite left = Sprite();
	Sprite right = Sprite();
	Sprite up = Sprite();
	Sprite down = Sprite();

public:
	virtual void levelUp() {}
	std::string getClassName() { return class_name; }
	std::string getName() { return name; }
	int getX() { return x; }
	int getY() { return y; }
	double getHealth() { return health; }
	double getXP() { return xp; }
	size_t invSlots() { return inv_slots; }
	size_t getLevel() { return level; }
	std::vector<int>* statusTurns() { return &status_turns; }
	std::vector<int>* statusVal() { return &status_val; }
	double getDamage() { return stats[0]; }
	double maxHealth() { return stats[1]; }
	double getDexterity() { return stats[2]; }
	double getAccuracy() { return stats[3]; }
	double getBalance() { return balance; }
	std::vector<Weapon>* getWeapons() { return &weapons; }
	std::vector<Armor>* getArmor() { return &armor; }
	std::vector<Potion>* getPotions() { return &potions; }

	void setX(int input) { x += input; }
	void setY(int input) { y += input; }
	void setHealth(int input) { health = input; }

	double addHealth(double input) {
		double temp;
		if (health + input <= stats[1]) {
			health += input; return 0;
		}
		else {
			temp = input - (stats[1] - health);
			health = stats[1];
			return temp;
		} // prevents health from going above max & returns any unused health
	}
	bool subtractHealth(double input) {
		if (health - input > 0) {
			health -= input; return false;
		}
		else return true;
	} // true = dead

	void addXP(double input) {
		xp += input;
	}

	virtual void mov(Direction dir, float d) {
		switch (dir) {
		case Direction::UP:
			up.y -= d;
			down.y -= d;
			right.y -= d;
			left.y -= d;
			break;
		case Direction::DOWN:
			up.y += d;
			down.y += d;
			right.y += d;
			left.y += d;
			break;
		case Direction::RIGHT:
			up.x += d;
			down.x += d;
			right.x += d;
			left.x += d;
			break;
		case Direction::LEFT:
			up.x -= d;
			down.x -= d;
			right.x -= d;
			left.x -= d;
			break;
		}
	}

	virtual void setPosX(float pos) {
		left.x = pos;
		right.x = pos;
		up.x = pos;
		down.x = pos;
	}
	virtual void setPosY(float pos) {
		left.y = pos;
		right.y = pos;
		up.y = pos;
		down.y = pos;
	}
	virtual void setPos(float pos) {
		setPosX(pos);
		setPosY(pos);
	}

public:
	Player()
		: x{ 50 }, y{ 50 }, // initialize these to the starting point
		xp{ 0 }, level{ 1 }, inv_slots{ 8 }, balance{ 0 }, stats{ 0, 100, 0, 0 }, status_turns{ 0,0,0,0,0,0,0,0,0 }, status_val{ 0,0,0,0 },
		weapons{ weapons_vector }, armor{ armor_vector }, potions{ potion_vector }, health{ 20 }{}

	Player(std::string name) : name{ name }, x{ 0 }, y{ 0 }, // initialize these to the starting point
		xp{ 0 }, level{ 0 }, inv_slots{ 0 }, balance{ 0 }, stats{ 0, 0, 0, 0 }, status_turns{ 0,0,0,0,0,0,0,0,0 }, status_val{ 0,0,0,0 },
		weapons{ NULL }, armor{ NULL }, potions{ NULL }, health{ 0 } {} // used for catching SDL_Quit()

	virtual ~Player() {}
};

class Fighter : public Player {
public:
	virtual void levelUp() override {
		level += 1;
		stats[0] += 4; stats[1] += 12; stats[2] += .4; stats[3] += .65;
		health = stats[1];
		std::cout << "You leveled up to level " << level << "! Your stats have increased to: \nMax Health: " << stats[1] <<
			"\nDamage: " << stats[0] << "\nDexterity: " << stats[2] / 20 * 100 << "%\nAccuracy: " << stats[3] / 20 * 100 << "%\n\nAs a reward, you have fully regenerated health!" << std::endl;
	}

	Fighter(std::string name) {
		this->class_name = "Fighter";
		this->name = name;
		health = 20;
		stats = { 8.5,20,5.5,17 };
		left	= Sprite("/resources/sprites/fighter_left.png", 300, 300);
		right	= Sprite("/resources/sprites/fighter_right.png", 300, 300);
		up		= Sprite("/resources/sprites/fighter_up.png", 300, 300);
		down	= Sprite("/resources/sprites/fighter_down.png", 300, 300);
	}
};

class Rogue : public Player {
public:
	virtual void levelUp() override {
		level += 1;
		stats[0] += 3; stats[1] += 10; stats[2] += .55; stats[3] += .7;
		health = stats[1];
		std::cout << "You leveled up to level " << level << "! Your stats have increased to: \nMax Health: " << stats[1] <<
			"\nDamage: " << stats[0] << "\nDexterity: " << stats[2] / 20 * 100 << "%\nAccuracy: " << stats[3] / 20 * 100 << "%\n\nAs a reward, you have fully regenerated health!" << std::endl;
	}

	Rogue(std::string name) {
		this->class_name = "Rogue";
		this->name = name;
		health = 16;
		stats = { 6,16,8,16 };
		left	= Sprite("/resources/sprites/rogue_left.png", 300, 300);
		right	= Sprite("/resources/sprites/rogue_right.png", 300, 300);
		up		= Sprite("/resources/sprites/rogue_up.png",	300, 300);
		down	= Sprite("/resources/sprites/rogue_down.png", 300, 300);
	}
};

class Wizard : public Player {
public:
	virtual void levelUp() override {
		level += 1;
		stats[0] += 2.5; stats[1] += 8; stats[2] += .45; stats[3] += .65;
		health = stats[1];
		std::cout << "You leveled up to level " << level << "! Your stats have increased to: \nMax Health: " << stats[1] <<
			"\nDamage: " << stats[0] << "\nDexterity: " << stats[2] / 20 * 100 << "%\nAccuracy: " << stats[3] / 20 * 100 << "%\n\nAs a reward, you have fully regenerated health!" << std::endl;
	}

	Wizard(std::string name) {
		this->class_name = "Wizard";
		this->name = name;
		health = 12;
		stats = { 6,12,6,16 };
		left	= Sprite("/resources/sprites/wizard_left.png", 300, 300);
		right	= Sprite("/resources/sprites/wizard_right.png", 300, 300);
		up		= Sprite("/resources/sprites/wizard_up.png", 300, 300);
		down	= Sprite("/resources/sprites/wizard_down.png", 300, 300);
	}
};

class Barbarian : public Player {
public:
	virtual void levelUp() override {
		level += 1;
		stats[0] += 7; stats[1] += 14; stats[2] += .375; stats[3] += .5;
		health = stats[1];
		std::cout << "You leveled up to level " << level << "! Your stats have increased to: \nMax Health: " << stats[1] <<
			"\nDamage: " << stats[0] << "\nDexterity: " << stats[2] / 20 * 100 << "%\nAccuracy: " << stats[3] / 20 * 100 << "%\n\nAs a reward, you have fully regenerated health!" << std::endl;
	}

	Barbarian(std::string name) {
		this->class_name = "Barbarian";
		this->name = name;
		health = 24;
		stats = { 12,24,4,12 };
		left	= Sprite("/resources/sprites/barbarian_left.png", 300, 300);
		right	= Sprite("/resources/sprites/barbarian_right.png", 300, 300);
		up		= Sprite("/resources/sprites/barbarian_up.png",	300, 300);
		down	= Sprite("/resources/sprites/barbarian_down.png", 300, 300);
	}
};

class Catgirl : public Player {
public:
	Sprite left;
	Sprite right;
	Sprite up;
	Sprite down;

public:
	virtual void levelUp() override {
		level += 1;
		stats[0] += 1; stats[1] += 4; stats[2] += .5; stats[3] += .6;
		health = stats[1];
		std::cout << "You leveled up to level " << level << "! Your stats have increased to: \nMax Health: " << stats[1] <<
			"\nDamage: " << stats[0] << "\nDexterity: " << stats[2] / 20 * 100 << "%\nAccuracy: " << stats[3] / 20 * 100 << "%\n\nAs a reward, you have fully regenerated health!" << std::endl;
	}

	Catgirl(std::string name) :
		left{ Sprite("resources/sprites/catgirl_left.png", 300, 300) },
		right{ Sprite("resources/sprites/catgirl_right.png", 300, 300) },
		up{ Sprite("resources/sprites/catgirl_up.png", 300, 300) },
		down{ Sprite("resources/sprites/catgirl_down.png", 300, 300) }
	{
		this->class_name = "Catgirl";
		this->name = name;
		health = 4;
		stats = { 3,4,7.5,14 };
		
	}
};