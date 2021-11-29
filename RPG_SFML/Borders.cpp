#include "Borders.h"

Borders::Borders()
{
}

Borders::Borders(sf::FloatRect inputrect, sf::FloatRect outputrect, sf::FloatRect maprect, sf::FloatRect statsrect, float linew, sf::Color c = sf::Color::White)
{
	inputbox.setTexture(nullptr);
	inputbox.setPosition(inputrect.left, inputrect.top);
	inputbox.setSize(sf::Vector2f(inputrect.width, inputrect.height));
	color(Box::INPUT, sf::Color::Transparent);
	inputbox.setOutlineThickness(linew);
	colorOutline(Box::INPUT, c);

	outputbox.setTexture(nullptr);
	outputbox.setPosition(outputrect.left, outputrect.top);
	outputbox.setSize(sf::Vector2f(outputrect.width, outputrect.height));
	color(Box::OUTPUT, sf::Color::Transparent);
	outputbox.setOutlineThickness(linew);
	colorOutline(Box::OUTPUT, c);

	mapbox.setTexture(nullptr);
	mapbox.setPosition(maprect.left, maprect.top);
	mapbox.setSize(sf::Vector2f(maprect.width, maprect.height));
	color(Box::MAP, sf::Color::Transparent);
	mapbox.setOutlineThickness(linew);
	colorOutline(Box::MAP, c);

	statsbox.setTexture(nullptr);
	statsbox.setPosition(statsrect.left, statsrect.top);
	statsbox.setSize(sf::Vector2f(statsrect.width, statsrect.height));
	color(Box::STATS, sf::Color::Transparent);
	statsbox.setOutlineThickness(linew);
	colorOutline(Box::STATS, c);
}

void Borders::draw(sf::RenderWindow& window) 
{
	window.draw(inputbox);
	sf::RenderStates rStates(texture);
	window.draw(outputbox, rStates);
	window.draw(mapbox);
	window.draw(statsbox);
}

void Borders::setTexture(const std::string& filePath)
{
	texture->loadFromFile(filePath);
	outputbox.setTexture(texture, true);
	outputbox.setOutlineThickness(0);
}

void Borders::setBorders(float linew, sf::Color c)
{
	inputbox.setOutlineThickness(linew);
	inputbox.setOutlineColor(c);
	outputbox.setOutlineThickness(linew);
	outputbox.setOutlineColor(c);
	mapbox.setOutlineThickness(linew);
	mapbox.setOutlineColor(c);
	statsbox.setOutlineThickness(linew);
	statsbox.setOutlineColor(c);
}

void Borders::colorOutline(Box box, sf::Color c)
{
	switch (box) {
	case Box::INPUT:
		inputbox.setOutlineColor(c);
		break;
	case Box::OUTPUT:
		outputbox.setOutlineColor(c);
		break;
	case Box::MAP:
		mapbox.setOutlineColor(c);
		break;
	case Box::STATS:
		statsbox.setOutlineColor(c);
		break;
	}
}

void Borders::color(Box box, sf::Color c)
{
	switch (box) {
	case Box::INPUT:
		inputbox.setFillColor(c);
		break;
	case Box::OUTPUT:
		outputbox.setFillColor(c);
		break;
	case Box::MAP:
		mapbox.setFillColor(c);
		break;
	case Box::STATS:
		statsbox.setFillColor(c);
		break;
	}
}

sf::FloatRect Borders::getBounds(Box b) 
{
	switch (b) {
	case Box::INPUT:
		return inputbox.getGlobalBounds();
		break;
	case Box::OUTPUT:
		return outputbox.getGlobalBounds();
		break;
	case Box::MAP:
		return mapbox.getGlobalBounds();
		break;
	case Box::STATS:
		return statsbox.getGlobalBounds();
		break;
	}
	return sf::FloatRect();
}