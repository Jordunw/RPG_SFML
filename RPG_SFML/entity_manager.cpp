#include "entity_manager.hpp"

namespace ecs
{

	EntityManager::EntityManager()
	{
		for (Entity entity = 0; entity < MAX_ENTITIES; entity++)
		{
			availableEntities.push(entity);
		}
	}

	Entity EntityManager::createEntity()
	{
		assert(livingEntityCount < MAX_ENTITIES && "Too many entities in existence");

		// take an id from the front of the queue
		Entity id = availableEntities.front();
		// remove the used id from the queue
		availableEntities.pop();
		// increment the amount of existing entities
		livingEntityCount++;

		return id;
	}

	void EntityManager::destroyEntity(Entity entity)
	{
		assert(entity < MAX_ENTITIES && "Entity out of range");

		// invalidate the entity's signature
		signatures[entity].reset();

		// put destroyed id at the end of the queue
		availableEntities.push(entity);
		livingEntityCount--;
	}

	void EntityManager::setSignature(Entity entity, Signature signature)
	{
		assert(entity < MAX_ENTITIES && "Entity out of range");

		signatures[entity] = signature;
	}

	Signature EntityManager::getSignature(Entity entity)
	{
		assert(entity < MAX_ENTITIES && "Entity out of range");

		return signatures[entity];
	}

}