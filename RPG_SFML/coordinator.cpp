#include "coordinator.hpp"

namespace ecs
{
	void Coordinator::init()
	{
		componentManager = std::make_unique<ComponentManager>();
		entityManager = std::make_unique<EntityManager>();
		systemManager = std::make_unique<SystemManager>();
	}

	Entity Coordinator::createEntity()
	{
		return entityManager->createEntity();
	}

	void Coordinator::destroyEntity(Entity entity)
	{
		entityManager->destroyEntity(entity);
		componentManager->entityDestroyed(entity);
		systemManager->entityDestroyed(entity);
	}
}