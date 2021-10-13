#pragma once
#include <SFML/Graphics.hpp>

#include <iostream>
#include <fstream>
#include <assert.h>
#include <stdexcept>
#include <unordered_map>

#include "Text.h"
//#include "Player.h"
#include "Borders.h"
#include "coordinator.hpp"
#include "Sprite.h"
#include "components.hpp"
#include "InputManager.h"
#include "EntityCreator.h"

class Game
{
public:
	Game() : entityCreator{ ecs::EntityCreator(coordinator) } { init(); }
	~Game() {}

public:
	void run();
	void exit();

private:
	// Initialization
	void init();				// inits everything
	void initializeSettings();	// grab settings from settings.txt
	void createBorders();		// create the base borders for the window
	void loadText();			// load ttfs
	void registerComponents();	// generate all of the components

	// Entities
	ecs::Entity createEntity(); // simple wrapper for creating entity

	// Text wrapper functions
	void setTextPos(std::string key, sf::Vector2f pos);
	void setTextColor(std::string key, sf::Color color);
	void setTextFont(std::string key, Fonts font);
	void setTextStyle(std::string key, sf::Text::Style style);
	void setText(std::string key, std::wstring text); // wstring to account for unicode chars
	void rotateText(std::string key, RotateDirection r);
	void drawText(std::string key);

	// Input
	void handleInput();

	// Rendering
	void renderGame();

private:
	bool running = true;

	sf::ContextSettings contextSettings;
	bool vsyncEnabled;

	unsigned int screenW = 1280;
	unsigned int screenH = 720;

	sf::RenderWindow window;

	sf::Clock clock;
	sf::Int32 deltaTime;

	InputManager inputManager;

	Borders borders;

	sf::Font lato, unicode, custom;
	// map from string name to text value
	//std::unordered_map<std::string, Text> textMap;
	
	std::vector<Text> outputText;
	Text inputText;

	// contains previous text
	std::vector<std::wstring> outputTextCache;
	std::vector<std::string> inputTextCache;

	sf::View outputTextView;
	sf::Vector2f textPosition;

	ecs::Coordinator coordinator;
	ecs::EntityCreator entityCreator;

	Sprite map = Sprite("resources/sprites/map.png", sf::IntRect(0, 0, 1280, 720), false);
	Sprite tree = Sprite("resources/sprites/tree.png", 150, 150, true, true);
};

