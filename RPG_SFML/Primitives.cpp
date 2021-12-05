#include "Primitives.h"
#include <glm/glm.hpp>

namespace jrpg
{

	AABB::AABB()
	{
		halfSize = size * .5f;
	}

	AABB::AABB(const sf::Vector2f& min, const sf::Vector2f& max)
	{
		size = max - min;
		halfSize = size * .5f;
	}

	sf::Vector2f AABB::getMin() const
	{
		return rigidBody.getPos() - halfSize;
	}

	sf::Vector2f AABB::getMax() const
	{
		return rigidBody.getPos() + halfSize;
	}

	Box::Box()
	{
		halfSize = size * .5f;
	}

	sf::Vector2f Box::getMin() const
	{
		return rigidBody.getPos() - halfSize;
	}

	sf::Vector2f Box::getMax() const 
	{
		return rigidBody.getPos() + halfSize;
	}

	sf::Vector2f Box::getHalfSize() const
	{
		return halfSize;
	}

	std::vector<sf::Vector2f> Box::getVertices() const
	{
		sf::Vector2f min = getMin();
		sf::Vector2f max = getMax();

		std::vector<sf::Vector2f> vertices = {
			{min.x, min.y},
			{min.x, max.y},
			{max.x, min.y},
			{max.x, max.y}
		};

		if (rigidBody.getRotation() != 0.0f) {
			for (auto& vert : vertices) {
				// implement this later
				// rotate point about center by rotation
				// jrpg::rotate(vert, rigidBody.getPos(), rigidBody.getRotation());
			}
		}

		return vertices;
	}

	RigidBody Box::getRigidBody() const
	{
		return rigidBody;
	}

	Box::Box(const sf::Vector2f& min, const sf::Vector2f& max)
	{
		size = max - min;
		halfSize = size * .5f;
	}

}