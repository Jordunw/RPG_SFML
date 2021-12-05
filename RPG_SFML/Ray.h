#pragma once
#include "VectorFunctions.h"

namespace jrpg
{

	class Ray
	{
	private:
		sf::Vector2f origin;
		sf::Vector2f direction;

	public:
		Ray(const sf::Vector2f& origin, const sf::Vector2f& direction) : origin{ origin }, direction{ direction }{}

	public:
		sf::Vector2f getOrigin() const { return origin; }
		sf::Vector2f getDirection() const { return direction; }
	};

}