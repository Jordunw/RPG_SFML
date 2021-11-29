#pragma once
#include "coordinator.hpp"
#include "components.hpp"
#include "Serialization.h"
#include <memory>

class ArchiveData
{
public:
	ArchiveData() {}
	ArchiveData(ecs::Coordinator* coordinator) : coordinator{ coordinator } {}

	~ArchiveData() { coordinator = nullptr; }

private:
	ecs::Coordinator* coordinator = nullptr;

	struct PlayerData
	{
		ecs::Name name = { "" };
		ecs::Depth depth = { 0 };
		ecs::XP xp = { 0 };
		ecs::Level level = { 0 };
		ecs::Inventory inventory = { 0 };
		ecs::Balance balance = { 0 };
		ecs::Velocity velocity = { {0, 0} };
		ecs::EntityType entityType = { 0 };
		ecs::ClassName className = { "" };
		ecs::Description description = { "" };
		ecs::Stats stats = { 0 };
		ecs::Status status = { 0 };
		ecs::LevelUpStats levelUpStats = { 0 };

		// ---------------------- SERIALIZATION ----------------------

	public:
		template<class Archive>
		void serialize(Archive& archive)
		{
			archive(
				CEREAL_NVP(name), 
				CEREAL_NVP(depth), 
				CEREAL_NVP(xp), 
				CEREAL_NVP(level), 
				CEREAL_NVP(inventory), 
				CEREAL_NVP(balance), 
				CEREAL_NVP(velocity), // probably not necessary
				CEREAL_NVP(entityType), // not necessary
				CEREAL_NVP(className), 
				CEREAL_NVP(description), // not necessary
				CEREAL_NVP(stats), 
				CEREAL_NVP(status), 
				CEREAL_NVP(levelUpStats)); // not necessary
		}

		// ---------------------- SERIALIZATION ----------------------
	} playerData;

public:
	ecs::Entity loadPlayer();
	void savePlayer(ecs::Entity e);

	// ---------------------- SERIALIZATION ----------------------

public:
	template<class Archive>
	void serialize(Archive& archive)
	{
		archive(CEREAL_NVP(playerData));
	}

	// ---------------------- SERIALIZATION ----------------------
};