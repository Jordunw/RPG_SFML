#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <Thor/Shapes.hpp>

// all necessary cereal headers included here
#include "Serialization.h"

#include <iostream>
#include <fstream>
#include <ostream>
#include <assert.h>
#include <stdexcept>
#include <unordered_map>
#include <filesystem>
#include <set>

//#include "Player.h"
#include "Borders.h"
#include "coordinator.hpp"
#include "Sprite.h"
#include "components.hpp"
#include "InputManager.h"
#include "EntityCreator.h"
#include "OutputTextManager.h"
#include "SettingsData.h"
#include "ArchiveData.h"
#include "Autocomplete.h"

enum class GameState {
	Intro,
	Running,
	Pause,
	Exit
};

class Game
{
public:
	Game() : entityCreator{ ecs::EntityCreator(coordinator) }, outputManager{ std::make_shared<unsigned int>(settingsData.screenW), std::make_shared<unsigned int>(settingsData.screenH) } { init(); }
	~Game() {}

public:
	void run();
	void exit();

private:
	// Initialization
	void init();				// inits everything
	void createBorders();		// create the base borders for the window
	void registerComponents();	// generate all of the components

	// loading data
	int load(const std::string& name);

	// saving data
	void save(const std::string& name);

	// Entities
	ecs::Entity createEntity(); // simple wrapper for creating entity

	void updateBounds();
	void updateBorderColor();

	// All input
	void handleInput();

	// Player typed input
	void handleInputLogic(const std::string& str);

	// Add autocomplete word to list
	void insertACWord(const std::string& word);

	// wrapper for the outputManager.print() function
	void printm(const std::string& str);
	// wrapper for the outputManager.printError() function
	void printe(const std::string& str);

	// Rendering
	void drawBoxes();
	void drawStats();
	void renderGame();

	void confirmExit();

private:
	GameState gameState = GameState::Intro;

	SettingsData settingsData;

	sf::ContextSettings contextSettings;

	sf::RenderWindow window;

	sf::Clock clock;
	float deltaTime;

	bool printFps = false;

	InputManager inputManager;
	bool gettingText = false;
	std::string inputText;
	sf::Text inputTextDrawable;

	std::shared_ptr<autoc::Node> autoComplete = std::make_shared<autoc::Node>();
	std::set<std::string> acWordList;

	sf::ConvexShape mapBox, statsBox, outputBox, displayBox;
	sf::RectangleShape inputBox;
	sf::FloatRect outputBoxBounds, inputBoxBounds, displayBoxBounds, mapBoxBounds, statsBoxBounds;

	OutputTextManager outputManager;

	ecs::Coordinator coordinator;
	ecs::EntityCreator entityCreator;

	ArchiveData archiveData;

	ecs::Entity player;

	// wrapper references so that i dont need to write settingsData. 800000 times
	const sf::Color& textColor = settingsData.textColor;
	const int& textSize = settingsData.textSize;
	const sf::Text::Style& textStyle = settingsData.textStyle;
	const Fonts& textFont = settingsData.textFont;


	// ---------------------- SERIALIZATION ----------------------

public:
	template<class Archive>
	inline void serialize(Archive& archive)
	{
		archive(settingsData, archiveData, CEREAL_NVP(acWordList));
	}

	// ---------------------- SERIALIZATION ----------------------
};

