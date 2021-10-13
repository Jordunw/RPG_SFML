#include "component_manager.hpp"

namespace ecs
{
	void ComponentManager::entityDestroyed(Entity entity)
	{
		// notify each component array that an entity has been destroyed
		// if it has a component for that entity, it will remove it
		for (auto const& pair : componentArrays)
		{
			auto const& component = pair.second;
			component->entityDestroyed(entity);
		}
	}
}