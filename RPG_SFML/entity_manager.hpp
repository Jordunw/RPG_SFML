#pragma once
#include <cinttypes>
#include <bitset>
#include <queue>
#include <array>
#include <assert.h>
#include <unordered_map>
#include <memory>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace ecs
{
	using Entity = std::uint32_t;

	const Entity MAX_ENTITIES = 5000;

	using ComponentType = std::uint8_t;

	const ComponentType MAX_COMPONENTS = 32;

	using Signature = std::bitset<MAX_COMPONENTS>;

	class EntityManager
	{
	public:
		EntityManager();

		Entity createEntity();

		void destroyEntity(Entity entity);
		void setSignature(Entity entity, Signature signature);
		Signature getSignature(Entity entity);

	private:
		std::queue<Entity> availableEntities{};

		std::array<Signature, MAX_ENTITIES> signatures{};

		uint32_t livingEntityCount{};
	};
}