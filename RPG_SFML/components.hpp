#pragma once

#include <glm/glm.hpp>

#include "Serialization.h"

#include <string>
#include "Sprite.h"

namespace ecs 
{
	struct EntityType
	{
		enum Type
		{
			drawable = 1, // does it have a sprite
			entity = 2, // e.g. player, shopkeep, sheep - anything that moves/is interactable with
			weapon = 4,
			armor = 8,
			potion = 16,
			item = 32, // can be used as either every other item that isnt weapon/armor/potion or could be overarching and encapsulate those types of items
		};

		unsigned int type;

		// SERIALIZATION
		template<class Archive>
		void serialize(Archive& archive)
		{
			archive(CEREAL_NVP(type));
		}
	};
	

	struct SpriteComponent
	{
		Sprite sprite;
	};

	struct ClassName
	{
		std::string className;

		// SERIALIZATION
		template<class Archive>
		void serialize(Archive& archive)
		{
			archive(CEREAL_NVP(className));
		}
	};

	struct Name
	{
		std::string name;

		// SERIALIZATION
		template<class Archive>
		void serialize(Archive& archive)
		{
			archive(CEREAL_NVP(name));
		}
	};

	struct XP
	{
		float xp;

		// SERIALIZATION
		template<class Archive>
		void serialize(Archive& archive)
		{
			archive(CEREAL_NVP(xp));
		}
	};

	struct Level
	{
		int level;

		// SERIALIZATION
		template<class Archive>
		void serialize(Archive& archive)
		{
			archive(CEREAL_NVP(level));
		}
	};

	struct Inventory
	{
		int slots;
		std::vector<Entity> items;

		// SERIALIZATION
		template<class Archive>
		void serialize(Archive& archive)
		{
			archive(CEREAL_NVP(slots), CEREAL_NVP(items));
		}
	};

	struct Balance
	{
		float balance;

		// SERIALIZATION
		template<class Archive>
		void serialize(Archive& archive)
		{
			archive(CEREAL_NVP(balance));
		}
	};

	struct Stats
	{
		struct Health
		{
			float base;
			float current;

			// SERIALIZATION
			template<class Archive>
			void serialize(Archive& archive)
			{
				archive(CEREAL_NVP(base), CEREAL_NVP(current));
			}
		} health;
		float dexterity;
		float accuracy;
		float damage;

		// SERIALIZATION
		template<class Archive>
		void serialize(Archive& archive)
		{
			archive(CEREAL_NVP(health), CEREAL_NVP(dexterity), CEREAL_NVP(accuracy), CEREAL_NVP(damage));
		}
	};

	// defines the increase in each stat a class gets on lvl up
	struct LevelUpStats
	{
		float health;
		float damage;
		float dexterity;
		float accuracy;

		// SERIALIZATION
		template<class Archive>
		void serialize(Archive& archive)
		{
			archive(CEREAL_NVP(health), CEREAL_NVP(damage), CEREAL_NVP(dexterity), CEREAL_NVP(accuracy));
		}
	};

	struct Status
	{
		// turns
		int poisoned;			   // -- takes damage per turn
		int healing;			   // -- healing over multiple turns
		int strengthened;		   // -- increases attack
		int shielded;			   // -- increases defense
		int weakened;			   // -- decreases attack
		int frightened;			   // -- cannot attack (can use items)
		int quicker;			   // -- higher dex
		int slower;				   // -- lower dex
		int stunned;			   // -- skips turn

		// strength
		float poisoned_multi;
		float healing_multi;
		float strength_multi;
		float shield_multi;
		float weakened_multi;
		float frightened_multi;
		float quicker_multi;
		float slower_multi;
		float stunned_multi;

		// SERIALIZATION
		template<class Archive>
		void serialize(Archive& archive)
		{
			archive(
				CEREAL_NVP(poisoned), 
				CEREAL_NVP(healing), 
				CEREAL_NVP(strengthened), 
				CEREAL_NVP(shielded), 
				CEREAL_NVP(weakened), 
				CEREAL_NVP(frightened), 
				CEREAL_NVP(quicker), 
				CEREAL_NVP(slower), 
				CEREAL_NVP(stunned), 
				CEREAL_NVP(poisoned_multi), 
				CEREAL_NVP(healing_multi), 
				CEREAL_NVP(strength_multi), 
				CEREAL_NVP(shield_multi), 
				CEREAL_NVP(weakened_multi), 
				CEREAL_NVP(frightened_multi), 
				CEREAL_NVP(quicker_multi), 
				CEREAL_NVP(slower_multi), 
				CEREAL_NVP(stunned_multi));
		}
	};

	struct Velocity
	{
		sf::Vector2f velocity;

		// SERIALIZATION
		template<class Archive>
		void serialize(Archive& archive)
		{
			archive(CEREAL_NVP(velocity));
		}
	};

	struct Depth
	{
		float depth;

		// SERIALIZATION
		template<class Archive>
		void serialize(Archive& archive)
		{
			archive(CEREAL_NVP(depth));
		}
	};

	struct TwoHanded
	{
		bool isTwoHanded;
	};

	struct DamageMulti
	{
		float multi;
	};

	struct BuyPrice
	{
		float buyPrice;
	};

	struct SellPrice
	{
		float sellPrice;
	};

	struct Equippable
	{
		enum Class
		{
			fighter = 1,
			rogue = 2,
			wizard = 4,
			barbarian = 8,
			catgirl = 16,
			all = 31
		};

		unsigned int equippable;
	};

	struct Equipped
	{
		bool equipped;
	};
	
	struct WeaponEffects
	{
		enum Effects
		{
			none = 0,
			light = 1,
			heavy = 2,
			bleed = 4,
			quick = 8,
			autism = 16,
			stun = 32,
			range = 64,
			defense = 128
		};

		unsigned int effects;
	};

	struct IsLegendary
	{
		bool isLegendary;
	};

	struct LegendaryEffects
	{
		enum Effects
		{
			flame = 1,
			engulf = 2,
			crush = 4,
			necrosis = 8,
			bloom = 16,
			concussion = 32,
			irishluck = 64
		};

		unsigned int effects;
	};

	struct Description
	{
		std::string description;

		// SERIALIZATION
		template<class Archive>
		void serialize(Archive& archive)
		{
			archive(CEREAL_NVP(description));
		}
	};

	struct ProtectionMulti
	{
		float multi;
	};

	// 0 -> weak (damage +25%)
	// 1 -> no effect
	// 2 -> resistant (damage -25%)
	struct ArmorWeakness
	{
		struct Types
		{
			unsigned char thrust;
			unsigned char slash;
			unsigned char bluntforce;
		} types;
	};

	// Potions
	// 
	// decimal value for multi (e.g. .3 would heal you for 30% of your total hp)
	struct EffectStrength
	{
		float effect;
	};

	// generally for potions
	struct Tier
	{
		int tier;
	};
}