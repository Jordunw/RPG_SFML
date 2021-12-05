#pragma once
#include <SFML/System/Vector2.hpp>
#include <vector>

namespace jrpg
{

	class RigidBody
	{
	private:
		sf::Vector2f pos;
		float rotation; // degrees

	public:
		sf::Vector2f getPos() const { return pos; }
		float getRotation() const { return rotation; }

		void setPos(const sf::Vector2f& newPos) { pos = newPos; }
		void setRotation(float newRotation) { rotation = newRotation; }
	};




	class Collider2D
	{
	protected:
		sf::Vector2f offset = sf::Vector2f();

	public:
		virtual float getInteriaTensor(float mass) const;
	};




	class Circle
	{
	private:
		float radius = 1.0f;
		RigidBody rigidBody = {};

	public:
		float getRadius() const { return radius; }
		sf::Vector2f getCenter() const { return rigidBody.getPos(); }
	};




	class AABB
	{
	private:
		sf::Vector2f size = sf::Vector2f();
		sf::Vector2f halfSize;
		RigidBody rigidBody = {};

	public:
		AABB();
		AABB(const sf::Vector2f& min, const sf::Vector2f& max);

	public:
		sf::Vector2f getMin() const;
		sf::Vector2f getMax() const;
	};




	class Box
	{
	private:
		sf::Vector2f size = sf::Vector2f();
		sf::Vector2f halfSize;
		RigidBody rigidBody = {};

	public:
		Box();
		Box(const sf::Vector2f& min, const sf::Vector2f& max);

	public:
		// will change these soon
		sf::Vector2f getMin() const;
		sf::Vector2f getMax() const;
		sf::Vector2f getHalfSize() const;
		std::vector<sf::Vector2f> getVertices() const;
		RigidBody getRigidBody() const;
	};
}