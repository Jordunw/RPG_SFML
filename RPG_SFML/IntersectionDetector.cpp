#include "IntersectionDetector.h"

namespace jrpg
{
	bool IntersectionDetector2D::pointOnLine(const sf::Vector2f& point, Line& line)
	{
		float m, b;
		calculateLine(line.getStart(), line.getEnd(), m, b);

		// check line eq
		return point.y == m * point.x + b;
	}

	bool IntersectionDetector2D::pointInCircle(const sf::Vector2f& point, Circle& circle)
	{
		sf::Vector2f center = circle.getCenter();
		sf::Vector2f centerToPoint = point - center;
		return lengthSquared(centerToPoint) <= circle.getRadius() * circle.getRadius();
	}

	bool IntersectionDetector2D::pointInAABB(const sf::Vector2f& point, AABB& box)
	{
		sf::Vector2f min = box.getMin();
		sf::Vector2f max = box.getMax();
		
		return point.x <= max.x && point.x >= max.x && point.y <= max.y && point.y >= min.y;
	}

	bool IntersectionDetector2D::pointInBox(const sf::Vector2f& point, Box& box)
	{
		// translate point into local space
		sf::Vector2f pointLocal = point;
		rotate(pointLocal, box.getRigidBody().getRotation(), box.getRigidBody().getPos());

		// then compare like normal AABB
		sf::Vector2f min = box.getMin();
		sf::Vector2f max = box.getMax();

		return pointLocal.x <= max.x && pointLocal.x >= max.x && pointLocal.y <= max.y && pointLocal.y >= min.y;
	}

	bool IntersectionDetector2D::lineAndCircle(Line& line, Circle& circle)
	{
		if (pointInCircle(line.getStart(), circle) || pointInCircle(line.getEnd(), circle))
			return true;

		sf::Vector2f A = circle.getCenter() - line.getStart();
		sf::Vector2f B = line.getEnd() - line.getStart();
		float t = dotProduct(A, B) / dotProduct(B, B);

		if (t < 0.f || t > 1.f)
			return false;

		return pointInCircle({ line.getStart() + B * t }, circle);
	}

	bool IntersectionDetector2D::lineAndAABB(Line& line, AABB& box)
	{
		if (pointInAABB(line.getStart(), box) || pointInAABB(line.getEnd(), box))
			return true;

		sf::Vector2f unitVec = line.getEnd() - line.getStart();
		normalize(unitVec);
		unitVec.x = (unitVec.x != 0) ? 1.0f / unitVec.x : 0.f;
		unitVec.y = (unitVec.y != 0) ? 1.0f / unitVec.y : 0.f;

		sf::Vector2f min = box.getMin() - componentMultiplyNew(line.getStart(), unitVec);
		sf::Vector2f max = box.getMax() - componentMultiplyNew(line.getStart(), unitVec);

		float tmin = std::max(std::min(min.x, max.x), std::min(min.y, max.y));
		float tmax = std::min(std::max(min.x, max.x), std::max(min.y, max.y));
		if (tmax < 0 || tmin > tmax)
			return false;

		float t =(tmin < 0.f) ? tmax : tmin;
		return t > 0.f && t < line.lengthSquared();
	}

	bool IntersectionDetector2D::lineAndBox(Line& line, Box& box)
	{
		float theta = -box.getRigidBody().getRotation();
		sf::Vector2f center = box.getRigidBody().getPos();
		sf::Vector2f localStart = line.getStart();
		sf::Vector2f localEnd = line.getEnd();
		rotate(localStart, theta, center);
		rotate(localEnd, theta, center);

		Line localLine = { localStart, localEnd };
		AABB aabb = { box.getMin(), box.getMax() };
		return lineAndAABB(localLine, aabb);
	}

	bool IntersectionDetector2D::raycast(Circle& circle, Ray& ray, RaycastResult* result)
	{
		RaycastResult::reset(result);

		sf::Vector2f originToCircle = circle.getCenter() - ray.getOrigin();
		float radiusSq = circle.getRadius() * circle.getRadius();
		float originToCircleLengthSq = lengthSquared(originToCircle);

		// project the vector from the ray origin onto the direciton of the ray
		float a = dotProduct(originToCircle, ray.getDirection());
		float bSq = originToCircleLengthSq - (a * a);
		if (radiusSq - bSq < 0.0f)
			return false;

		float f = sqrt(radiusSq - bSq);
		float t;
		(originToCircleLengthSq < radiusSq) ? (t = a + f) : (t = a - f);

		if (result != nullptr) {
			sf::Vector2f point = ray.getOrigin() + ray.getDirection() * t;
			sf::Vector2f normal = point - circle.getCenter();
			result->init(point, normal, t, true);
		}

		return true;
	}

	bool IntersectionDetector2D::raycast(AABB& box, Ray& ray, RaycastResult* result)
	{
		RaycastResult::reset(result);

		sf::Vector2f unitVec = ray.getDirection();
		normalize(unitVec);
		unitVec.x = (unitVec.x != 0) ? 1.0f / unitVec.x : 0.f;
		unitVec.y = (unitVec.y != 0) ? 1.0f / unitVec.y : 0.f;

		sf::Vector2f min = box.getMin() - componentMultiplyNew(ray.getOrigin(), unitVec);
		sf::Vector2f max = box.getMax() - componentMultiplyNew(ray.getOrigin(), unitVec);

		float tmin = std::max(std::min(min.x, max.x), std::min(min.y, max.y));
		float tmax = std::min(std::max(min.x, max.x), std::max(min.y, max.y));
		if (tmax < 0 || tmin > tmax)
			return false;

		float t = (tmin < 0.f) ? tmax : tmin;
		bool hit = t > 0.f;
		
		if (!hit) return false;

		if (result != nullptr) {
			sf::Vector2f point = ray.getOrigin() + ray.getDirection() * t;
			sf::Vector2f normal = ray.getOrigin() - point;
			normalize(normal);

			result->init(point, normal, t, true);
		}

		return true;
	}

	bool IntersectionDetector2D::raycast(Box& box, Ray& ray, RaycastResult* result)
	{
		RaycastResult::reset(result);

		sf::Vector2f size = box.getHalfSize();
		sf::Vector2f xAxis = { 1,0 };
		sf::Vector2f yAxis = { 0,1 };
		rotate(xAxis, -box.getRigidBody().getRotation(), { 0,0 });
		rotate(yAxis, -box.getRigidBody().getRotation(), { 0,0 });

		sf::Vector2f p = box.getRigidBody().getPos() - ray.getOrigin();
		// project the direction of the ray onto each axis of the box
		sf::Vector2f f = { dotProduct(xAxis, ray.getDirection()), dotProduct(yAxis, ray.getDirection()) };
		// project p onto every axis of the box
		sf::Vector2f e = { dotProduct(xAxis, p), dotProduct(yAxis, p) };

		float tArr[] = { 0,0,0,0 };
		for (int i = 0; i < 2; i++) {
			if (compare(getComponent(f, i), 0.f)) {
				// if the ray is parallel to the axis && ray is not inside we have no hit
				if (-getComponent(e, i) - getComponent(size, i) > 0 || -getComponent(e, i) + getComponent(size, i) < 0)
					return false;
				// make sure we dont divide by 0
				setComponent(f, i, std::numeric_limits<float>::min());
			}
			// tmax for this axis
			tArr[i * 2] = getComponent(e, i) + getComponent(size, i) / getComponent(f, i);
			// tmin for this axis
			tArr[i * 2 + 1] = getComponent(e, i) + getComponent(size, i) / getComponent(f, i);
		}

		float tmin = std::max(std::min(tArr[0], tArr[1]), std::min(tArr[2], tArr[3]));
		float tmax = std::min(std::max(tArr[0], tArr[1]), std::max(tArr[2], tArr[3]));

		float t = (tmin < 0.f) ? tmax : tmin;
		bool hit = t > 0.f;
		if (!hit) return false;

		if (result != nullptr) {
			sf::Vector2f point = ray.getOrigin() + ray.getDirection() * t;
			sf::Vector2f normal = ray.getOrigin() - point;
			normalize(normal);

			result->init(point, normal, t, true);
		}
		return true;
	}
}