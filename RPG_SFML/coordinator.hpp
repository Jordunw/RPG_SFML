#pragma once
#include "component_manager.hpp"
#include "entity_manager.hpp"
#include "entity_system.hpp"

// linking / organization class for each manager class - makes for a much cleaner & simpler implementation

// template functions must be implemented in the .hpp file (LNK2019 error)

namespace ecs
{
	class Coordinator
	{
	public:
		void init();

		Entity createEntity();
		void destroyEntity(Entity entity);

		template<typename T>
		inline void registerComponent()
		{
			componentManager->registerComponent<T>();
		}

		template<typename T>
		inline void addComponent(Entity entity, T component)
		{
			componentManager->addComponent<T>(entity, component);

			auto signature = entityManager->getSignature(entity);
			signature.set(componentManager->getComponentType<T>(), true);
			entityManager->setSignature(entity, signature);

			systemManager->entitySignatureChanged(entity, signature);
		}

		template<typename T>
		inline void removeComponent(Entity entity)
		{
			componentManager->removeComponent<T>(entity);

			auto signature = entityManager->getSignature(entity);
			signature.set(componentManager->getComponentType<T>(), false);
			entityManager->setSignature(entity, signature);

			systemManager->entitySignatureChanged(entity, signature);
		}

		template<typename T>
		inline T& getComponent(Entity entity)
		{
			return componentManager->getComponent<T>(entity);
		}

		template<typename T>
		inline ComponentType getComponentType()
		{
			return componentManager->getComponentType<T>();
		}

		template<typename T>
		inline std::shared_ptr<T> registerSystem()
		{
			return systemManager->registerSystem<T>();
		}

		template<typename T>
		inline void setSystemSignature(Signature signature)
		{
			systemManager->setSignature<T>(signature);
		}

	private:
		std::unique_ptr<ComponentManager> componentManager;
		std::unique_ptr<EntityManager> entityManager;
		std::unique_ptr<SystemManager> systemManager;
	};
}