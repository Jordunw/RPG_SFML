#pragma once
#include <SFML/System/Vector2.hpp>
#include <cmath>
#include <assert.h>

namespace jrpg
{
	constexpr float pi = 3.14159265358979;
	constexpr float toRadsConst = pi / 180.f;
	constexpr float toDegreesConst = 180.f / pi;

	float getComponent(const sf::Vector2f& vec, int component) {
		assert(component == 0 || component == 1 && "Trying to get a nonexistent component of a vector");
		return !component ? vec.x : vec.y;
	}

	void setComponent(sf::Vector2f& vec, int component, float val) {
		assert(component == 0 || component == 1 && "Trying to set a nonexistent component of a vector");
		!component ? (vec.x = val) : (vec.y = val);
	}

	float toRadians(float degrees)
	{
		return degrees * toRadsConst;
	}

	float toDegrees(float radians)
	{
		return radians * toDegreesConst;
	}

	float lengthSquared(const sf::Vector2f& vec)
	{
		return vec.x * vec.x + vec.y * vec.y;
	}

	float length(const sf::Vector2f& vec)
	{
		return sqrt(lengthSquared(vec));
	}

	void componentMultiply(sf::Vector2f& product, const sf::Vector2f& multiplier)
	{
		product.x *= multiplier.x;
		product.y *= multiplier.y;
	}

	sf::Vector2f componentMultiplyNew(const sf::Vector2f& product, const sf::Vector2f& multiplier)
	{
		return { product.x * multiplier.x, product.y * multiplier.y };
	}

	// gets the distance squared between two points
	float distanceSquared(const sf::Vector2f& point1, const sf::Vector2f& point2)
	{
		sf::Vector2f dist = point1 - point2;
		return dist.x * dist.x + dist.y * dist.y;
	}

	float distance(const sf::Vector2f& point1, const sf::Vector2f& point2)
	{
		return sqrt(distanceSquared(point1, point2));
	}

	void rotate(sf::Vector2f& vec, float angleDeg, const sf::Vector2f& origin)
	{
		float x = vec.x - origin.x;
		float y = vec.y - origin.y;

		float cos = std::cos(toRadians(angleDeg));
		float sin = std::sin(toRadians(angleDeg));

		float xPrime = x * cos - y * sin;
		float yPrime = x * sin + y * cos;

		xPrime += origin.x;
		yPrime += origin.y;

		vec = { xPrime, yPrime };
	}

	// if running into problems check this
	bool compare(float x, float y, float epsilon = std::numeric_limits<float>::epsilon())
	{
		return abs(x - y) <= epsilon * std::max(1.f, std::max(abs(x), abs(y)));
	}

	bool compare(const sf::Vector2f& vec1, const sf::Vector2f& vec2, float epsilon = std::numeric_limits<float>::epsilon())
	{
		return compare(vec1.x, vec2.x, epsilon) && compare(vec1.y, vec2.y, epsilon);
	}

	float dotProduct(const sf::Vector2f& vec1, const sf::Vector2f& vec2)
	{
		return vec1.x * vec2.x + vec1.y * vec2.y;
	}

	// normalizes the passed in vector (MODIFIES DOESNT RETURN)
	void normalize(sf::Vector2f& vec)
	{
		float l = length(vec);
		vec /= l;
	}

	// same as normalize function but returns a new vector instead of modifying it
	sf::Vector2f normalizeNew(const sf::Vector2f& vec)
	{
		return vec / length(vec);
	}

	void calculateLine(const sf::Vector2f& start, const sf::Vector2f& end, float& m, float& b)
	{
		float dy = end.y - start.y;
		float dx = end.x - start.x;
		if (dx == 0.f)
			dx = std::numeric_limits<float>::min();
		m = dy / dx;
		b = end.y - (m * end.x);
	}

	// returns the perpendicular to the line
	void calculateLinePerpendicular(const sf::Vector2f& start, const sf::Vector2f& end, float& m, float& b)
	{
		float dy = end.y - start.y;
		float dx = end.x - start.x;
		if (dy == 0.f)
			dy = std::numeric_limits<float>::min();
		m = -dx / dy;
		b = end.y - (m * end.x);
	}

	// returns the perpendicular to the line through a point
	void calculateLinePerpendicularThroughPoint(const sf::Vector2f& start, const sf::Vector2f& end, float& m, float& b, const sf::Vector2f& point)
	{
		float dy = end.y - start.y;
		float dx = end.x - start.x;
		if (dy == 0.f)
			dy = std::numeric_limits<float>::min();
		m = -dx / dy;
		b = point.y - (m * point.x);
	}

}