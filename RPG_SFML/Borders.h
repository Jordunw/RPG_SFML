#pragma once
#include <SFML/Graphics.hpp>
#include "Enum.h"

class Borders {
private:
	sf::Texture* texture;

	sf::RectangleShape mapbox;
	sf::RectangleShape statsbox;
	sf::RectangleShape outputbox;
	sf::RectangleShape inputbox;

public:
	Borders();
	Borders(sf::FloatRect, sf::FloatRect, sf::FloatRect, sf::FloatRect, float, sf::Color);
	~Borders() {}

public:
	void setTexture(const std::string& filePath);
	void setBorders(float, sf::Color);
	void draw(sf::RenderWindow& window);
	void colorOutline(Box, sf::Color);
	void color(Box, sf::Color);

public:
	sf::FloatRect getBounds(Box);
};