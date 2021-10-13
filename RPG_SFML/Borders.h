#pragma once
#include <SFML/Graphics.hpp>
#include "Enum.h"

constexpr float oneThird = 0.33333333333f;
constexpr float twoThirds = 0.66666666666f;

class Borders {
private:
	sf::RectangleShape mapbox;
	sf::RectangleShape statsbox;
	sf::RectangleShape outputbox;
	sf::RectangleShape inputbox;

public:
	Borders();
	Borders(sf::FloatRect, sf::FloatRect, sf::FloatRect, sf::FloatRect, float, sf::Color);
	~Borders();

public:
	void setBorders(float, sf::Color);
	void draw(sf::RenderWindow& window);
	void colorOutline(Box, sf::Color);
	void color(Box, sf::Color);

public:
	sf::FloatRect getBounds(Box);
};