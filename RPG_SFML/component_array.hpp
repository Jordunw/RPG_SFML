#pragma once
#include "entity_manager.hpp"

#include <unordered_map>

// Has to be inline to fix LNK2019 compile errors

namespace ecs
{

	class IComponentArray
	{
	public:
		virtual ~IComponentArray() = default;
		virtual void entityDestroyed(Entity entity) = 0;
	};

	template<typename T>
	class ComponentArray : public IComponentArray
	{
	public:
		inline void insertData(Entity entity, T component)
		{
			assert(entityToIndexMap.find(entity) == entityToIndexMap.end() && "Component added to same entity more than once");

			size_t newIndex = size;
			entityToIndexMap[entity] = newIndex;
			indexToEntityMap[newIndex] = entity;
			componentArray[newIndex] = component;
			size++;
		}
		inline void removeData(Entity entity)
		{
			assert(entityToIndexMap.find(entity) != entityToIndexMap.end() && "Removing nonexistent component");

			// copy end element to deleted elements place to preserve density
			size_t indexOfRemovedEntity = entityToIndexMap[entity];
			size_t indexOfLastElement = size - 1;
			componentArray[indexOfRemovedEntity] = componentArray[indexOfLastElement];

			Entity entityOfLastElement = indexToEntityMap[indexOfLastElement];
			entityToIndexMap[entityOfLastElement] = indexOfRemovedEntity;
			indexToEntityMap[indexOfRemovedEntity] = entityOfLastElement;

			entityToIndexMap.erase(entity);
			indexToEntityMap.erase(indexOfLastElement);

			size--;
		}
		inline T& getData(Entity entity)
		{
			assert(entityToIndexMap.find(entity) != entityToIndexMap.end() && "Retrieving nonexistent entity");

			return componentArray[entityToIndexMap[entity]];
		}
		inline void entityDestroyed(Entity entity) override
		{
			if (entityToIndexMap.find(entity) != entityToIndexMap.end())
				removeData(entity);
		}

	private:
		// packed array of components
		std::array<T, MAX_ENTITIES> componentArray;

		// map from entity id to array index
		std::unordered_map<Entity, size_t> entityToIndexMap;

		// map from array index to entity id
		std::unordered_map<size_t, Entity> indexToEntityMap;

		size_t size;
	};

}