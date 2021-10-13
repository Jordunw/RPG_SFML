#pragma once
#include <SFML/System.hpp>
#include <unordered_map>

class InputManager
{
public:
	void update();

	void pressKey(unsigned int keyID);
	void releaseKey(unsigned int keyID);

	void setMouseCoords(float x, float y);
	sf::Vector2f getMouseCoords() const { return mouseCoords; }

	bool isKeyDown(unsigned int keyID);
	bool isKeyPressed(unsigned int keyID);

private:
	bool wasKeyDown(unsigned int keyID);

private:
	std::unordered_map<unsigned int, bool> keyMap;
	std::unordered_map<unsigned int, bool> prevKeyMap;
	sf::Vector2f mouseCoords;
};

