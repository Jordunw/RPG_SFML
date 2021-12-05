#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <assert.h>

namespace jrpg {

	class Line
	{
	protected:
		sf::Vector2f from;
		sf::Vector2f to;

	public:
		Line(){}
		Line(const sf::Vector2f& from, const sf::Vector2f& to)
			: from{ from }, to{ to } {}

	public:
		sf::Vector2f getFrom() const { return from; }
		sf::Vector2f getTo() const { return to; }
		// same functions different names
		sf::Vector2f getStart() const { return from; }
		sf::Vector2f getEnd() const { return to; }

		float lengthSquared() const { 
			sf::Vector2f v = to - from; 
			return (to.x * to.x + to.y * to.y);
		}

		// make sure to check that lifetime > 0
	};

	class LineDrawable : public Line
	{
	public:
		enum Point {
			start = 0,
			end = 1
		};
	private:
		sf::Color color[2];
		int lifetime;

	public:
		LineDrawable(const sf::Vector2f& from, const sf::Vector2f& to, const sf::Color& color1, const sf::Color& color2, int lifetime)
			: color{ color1, color2 }, lifetime{ lifetime }
		{
			this->from = from;
			this->to = to;
		}

	public:
		int beginFrame() { return --lifetime; }
		void draw(sf::RenderWindow& window) const {
			sf::Vertex vertices[] = {
				{from, color[0]},
				{to, color[1]}
			};
			window.draw(vertices, 2, sf::Lines);
		}
		sf::Color getColor(Point point) const { return color[point]; }
	};

}