#include "entity_system.hpp"

namespace ecs
{
	template<typename T>
	std::shared_ptr<T> SystemManager::registerSystem()
	{
		const char* typeName = typeid(T).name();

		assert(systems.find(typeName) == systems.end() && "Registering system more than once");

		// create a pointer to the system and return it so it can be used externally
		auto system = std::make_shared<T>();
		systems.insert({ typeName, system });
		return system;
	}

	template<typename T>
	void SystemManager::setSignature(Signature signature)
	{
		const char* typeName = typeid(T).name();

		assert(systems.find(typeName) != systems.end() && "System used before being registered");

		// set system signature
		signatures.insert({ typeName, signature });
	}

	void SystemManager::entityDestroyed(Entity entity)
	{
		// erase a destroyed identity from all the system lists
		// no check needed since its a set
		for (auto const& pair : systems)
		{
			auto const& system = pair.second;
			system->entities.erase(entity);
		}
	}

	void SystemManager::entitySignatureChanged(Entity entity, Signature entitySignature)
	{
		// notify each system that an entity's signature changed
		for (auto const& pair : systems)
		{
			auto const& type = pair.first;
			auto const& system = pair.second;
			auto const& systemSignature = signatures[type];

			// if the entity signature matches the system signature then insert into set
			if ((entitySignature & systemSignature) == systemSignature)
			{
				system->entities.insert(entity);
			}
			else // erase from set
			{
				system->entities.erase(entity);
			}
		}
	}
}