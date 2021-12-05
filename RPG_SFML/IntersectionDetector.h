#pragma once
#include "Primitives.h"
#include "Line.h"
#include "VectorFunctions.h"
#include "Ray.h"
#include "RaycastResult.h"

namespace jrpg
{

	// static class to detect intersections between points, lines, and primitives
	class IntersectionDetector2D
	{
	public:
		// point v primitive
		static bool pointOnLine(const sf::Vector2f& point, Line& line);
		static bool pointInCircle(const sf::Vector2f& point, Circle& circle);
		static bool pointInAABB(const sf::Vector2f& point, AABB& box);
		static bool pointInBox(const sf::Vector2f& point, Box& box);

		// line v primitive
		static bool lineAndCircle(Line& line, Circle& circle);
		static bool lineAndAABB(Line& line, AABB& box);
		static bool lineAndBox(Line& line, Box& box);

		// raycasts
		static bool raycast(Circle& circle, Ray& ray, RaycastResult* result);
		static bool raycast(AABB& box, Ray& ray, RaycastResult* result);
		static bool raycast(Box& box, Ray& ray, RaycastResult* result);
	};

}