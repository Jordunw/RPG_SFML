#pragma once
#include "entity_manager.hpp"

#include <set>
#include <memory>
#include <unordered_map>
#include <string>

namespace ecs
{
	class System
	{
	public:
		std::set<Entity> entities; // insert() and erase() autocheck if an entity is in the list & does nothing if it is already there

	};

	class SystemManager
	{
	public:
		template<typename T>
		std::shared_ptr<T> registerSystem();

		template<typename T>
		void setSignature(Signature signature);

		void entityDestroyed(Entity entity);

		void entitySignatureChanged(Entity entity, Signature entitySignature);

	private:
		std::unordered_map<std::string, Signature> signatures{};
		std::unordered_map<std::string, std::shared_ptr<System>> systems{};
	};
}