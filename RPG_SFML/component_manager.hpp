#pragma once
#include "entity_manager.hpp"
#include "component_array.hpp"

#include <memory>

namespace ecs 
{

	class ComponentManager
	{
	public:
		template<typename T>
		inline void registerComponent()
		{
			const char* typeName = typeid(T).name();

			assert(componentTypes.find(typeName) == componentTypes.end() && "Registering component type more than once");
			// add this componentType to the map
			componentTypes.insert({ typeName, nextComponentType });
			// create a pointer and add it to the arrays map
			componentArrays.insert({ typeName, std::make_shared<ComponentArray<T>>() });

			nextComponentType++;
		}

		template<typename T>
		inline ComponentType getComponentType()
		{
			const char* typeName = typeid(T).name();

			assert(componentTypes.find(typeName) != componentTypes.end() && "Component not registered before use");

			return componentTypes[typeName];
		}

		template<typename T>
		inline void addComponent(Entity entity, T component)
		{
			// add a component to the array for an entity
			getComponentArray<T>()->insertData(entity, component);
		}

		template<typename T>
		inline void removeComponent(Entity entity)
		{
			// remove a component from the array for an entity
			getComponentArray<T>()->removeData(entity);
		}

		template<typename T>
		inline T& getComponent(Entity entity) 
		{
			// get a reference to a component from the array for an entity
			return getComponentArray<T>()->getData(entity);
		}

		void entityDestroyed(Entity entity);

	private:
		// map from string pointer to componentType
		std::unordered_map<const char*, ComponentType> componentTypes{};
		// map from string pointer to componentArray
		std::unordered_map<const char*, std::shared_ptr<IComponentArray>> componentArrays{};
		// component type to be assigned to the next registered component - starts at 0
		ComponentType nextComponentType{};

		template<typename T>
		inline std::shared_ptr<ComponentArray<T>> getComponentArray()
		{
			const char* typeName = typeid(T).name();

			assert(componentTypes.find(typeName) != componentTypes.end() && "Component not registered before use");

			return std::static_pointer_cast<ComponentArray<T>>(componentArrays[typeName]);
		}
	};

}