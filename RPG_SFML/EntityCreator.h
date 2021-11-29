#pragma once
#include "coordinator.hpp"
#include "Sprite.h"
#include "components.hpp"

namespace ecs
{
	enum class PlayerClass
	{
		fighter,
		rogue,
		wizard,
		barbarian,
		catgirl
	};

	enum class WeaponType
	{
		dagger,
		club,
		greatclub,
		axe,
		mace,
		quarterstaff,
		sickle,
		trident,
		katana,
		battleaxe,
		flail,
		glaive,
		halberd,
		longsword,
		maul,
		morningstar,
		rapier,
		pickaxe,
		shortsword,
		battlehammer,
		woodenspoon,
		sabre,
		broadsword,
		greatsword,
		handaxe,
		fryingpan,
		kelloggs,
		henry,
		bonsai,
		gfp,
		kingsdaggers,
		warpick,
		laevateinn,
		thunderscry,
		blarneystone
	};

	enum class ArmorType
	{
		crackedleather,
		leather,
		chainmail,
		rustedplate,
		ironplate
	};

	enum class PotionType
	{
		healing,
		regeneration,
		strength,
		defense,
		invis
	};

	class EntityCreator
	{
	public:
		EntityCreator(ecs::Coordinator& coordinator) : coordinator{ coordinator } {}
	private:
		Coordinator& coordinator;

	public:
		Entity createGeneralCharacter(std::string name, Sprite sprite, std::string description, float depth);
		Entity createGeneralCharacter(std::string name, std::string textureLocation, sf::Vector2f pos, std::string description, float depth);
		Entity createPlayer(PlayerClass pClass, std::string name);
		Entity createWeapon(WeaponType wType);
		Entity createArmor(ArmorType aType);
		Entity createPotion(PotionType pType);
	};

}