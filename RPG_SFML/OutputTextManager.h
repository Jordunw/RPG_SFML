#pragma once
#include "Text.h"
#include <string>

class OutputTextManager
{
public:
	OutputTextManager(){}

private:
	sf::Font unicode, lato;
	sf::View view;
	std::vector<Text> text;
	std::vector<std::wstring> cache;
	sf::Vector2f pos;

public:
	// draw text on screen
	void draw(sf::RenderWindow& window);
	// add text to buffer
	void print(const std::wstring& str,
		sf::Color c = sf::Color::White,
		float size = 16,
		sf::Text::Style style = sf::Text::Style::Regular);
	// scroll the window
	void scroll(float dist);
};

