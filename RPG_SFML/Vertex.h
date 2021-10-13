#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

std::vector<sf::VertexArray> createBoxes() {
	sf::VertexArray mapBox(sf::LineStrip, 4), textBox(sf::LineStrip, 4), outputBox(sf::LineStrip, 4), inputBox(sf::LineStrip, 4);
	mapBox[0].position = sf::Vector2f(0,0);
	mapBox[1].position = sf::Vector2f(1280 * (2 / 3), 0);
	mapBox[2].position = sf::Vector2f(1280 * (2 / 3), 720 * (3 / 4));
	mapBox[3].position = sf::Vector2f(0, 720 * (3 / 4));
	mapBox[4].position = sf::Vector2f(0, 0);

	return std::vector<sf::VertexArray> {mapBox, textBox, outputBox, inputBox};
}