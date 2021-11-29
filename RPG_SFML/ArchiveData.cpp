#include "ArchiveData.h"

ecs::Entity ArchiveData::loadPlayer()
{
	ecs::Entity e = coordinator->createEntity();
	coordinator->addComponent<ecs::Name>(e, playerData.name);
	coordinator->addComponent<ecs::Depth>(e, playerData.depth);
	coordinator->addComponent<ecs::XP>(e, playerData.xp);
	coordinator->addComponent<ecs::Level>(e, playerData.level);
	coordinator->addComponent<ecs::Inventory>(e, playerData.inventory);
	coordinator->addComponent<ecs::Balance>(e, playerData.balance);
	coordinator->addComponent<ecs::Velocity>(e, playerData.velocity);
	coordinator->addComponent<ecs::EntityType>(e, playerData.entityType);
	coordinator->addComponent<ecs::ClassName>(e, playerData.className);
	coordinator->addComponent<ecs::Description>(e, playerData.description);
	coordinator->addComponent<ecs::Stats>(e, playerData.stats);
	coordinator->addComponent<ecs::Status>(e, playerData.status);
	coordinator->addComponent<ecs::LevelUpStats>(e, playerData.levelUpStats);

	return e;
}

void ArchiveData::savePlayer(ecs::Entity e)
{
	playerData.name = coordinator->getComponent<ecs::Name>(e);
	playerData.depth = coordinator->getComponent<ecs::Depth>(e);
	playerData.xp = coordinator->getComponent<ecs::XP>(e);
	playerData.level = coordinator->getComponent<ecs::Level>(e);
	playerData.inventory = coordinator->getComponent<ecs::Inventory>(e);
	playerData.balance = coordinator->getComponent<ecs::Balance>(e);
	playerData.velocity = coordinator->getComponent<ecs::Velocity>(e);
	playerData.entityType = coordinator->getComponent<ecs::EntityType>(e);
	playerData.className = coordinator->getComponent<ecs::ClassName>(e);
	playerData.description = coordinator->getComponent<ecs::Description>(e);
	playerData.stats = coordinator->getComponent<ecs::Stats>(e);
	playerData.status = coordinator->getComponent<ecs::Status>(e);
	playerData.levelUpStats = coordinator->getComponent<ecs::LevelUpStats>(e);
}
