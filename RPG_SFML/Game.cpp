#include "Game.h"
#include <Windows.h>
#include <shellapi.h>
#include <stdio.h>
#include <cstdio>
#include "Hash.h"
#include <SDL2/SDL.h>

void Game::run()
{
	while (gameState != GameState::Exit)
	{
		handleInput();
		renderGame();
	}
}

void Game::exit()
{
	window.close();
	// do any other cleanup
}

void Game::init()
{
	window.create(sf::VideoMode(settingsData.screenW, settingsData.screenH), "JordunRPG", settingsData.windowStyle, contextSettings);
	window.setVerticalSyncEnabled(settingsData.vsyncEnabled);
	
	createBorders();
	updateBounds();

	outputManager = OutputTextManager(std::make_shared<unsigned int>(settingsData.screenW), std::make_shared<unsigned int>(settingsData.screenH));
	outputManager.init();
	outputManager.resetView(sf::FloatRect(0, 0, (oneThird - .01f) * settingsData.screenW, settingsData.screenH * (twoThirds - .06f)));
	outputManager.setViewport(sf::FloatRect(twoThirds + .01f, .015f, 0.3233f, twoThirds - .06f));

	inputTextDrawable.setFont(outputManager.getFont(Fonts::unicode));
	inputTextDrawable.setPos({ inputBoxBounds.left + 2, inputBoxBounds.top + 6 });
	inputTextDrawable.color(sf::Color::White);
	inputTextDrawable.size(16);

	// list of predefined words to be added to the autocompleter
	// not necessary but makes it extremely easy to add words whenever i add commands or whatever
	// this should be ordered by how common words will probably be
	acWordList = std::set<std::string>({
		"help",
		"fps",
		"color",
		"clear",
		"borders",
		"text",
		"rgb",
		"define",
		"load",
		"save",
		"say",
		"print",
		"vsync",
		"window",
		"resize",
		"akira3k",
		"exit",
		"quit"
		});

	for (auto& str : acWordList)
		autoc::insert(&autoComplete, str);

	coordinator.init();
	registerComponents();

	player = entityCreator.createPlayer(ecs::PlayerClass::fighter, "nigga");
	archiveData = ArchiveData(&coordinator);
}

void Game::createBorders()
{

	displayBox = thor::Shapes::roundedRect(
		{ static_cast<float>(settingsData.screenW) * twoThirds - 5, static_cast<float>(settingsData.screenH) * .25f - 6 },
		4.f,
		sf::Color::Transparent,
		2.f,
		sf::Color(197, 239, 247, 255)
		);
	displayBox.setPosition(3.f, static_cast<float>(settingsData.screenH) * .75f + 4);

	outputBox = thor::Shapes::roundedRect(
		{ static_cast<float>(settingsData.screenW) * oneThird - 7, static_cast<float>(settingsData.screenH) * twoThirds - 5 },
		4.f,
		sf::Color::Transparent,
		2.f,
		sf::Color(197, 239, 247, 255)
	);
	outputBox.setPosition(static_cast<float>(settingsData.screenW) * twoThirds + 4, 3.f);

	inputBox = sf::RectangleShape({ static_cast<float>(settingsData.screenW) * oneThird - 21, 24.f });
	inputBox.setOutlineColor(sf::Color(197, 239, 247, 255));
	inputBox.setFillColor(sf::Color::Transparent);
	inputBox.setOutlineThickness(2.f);
	inputBox.setPosition(static_cast<float>(settingsData.screenW) * twoThirds + 11, outputBox.getGlobalBounds().top + outputBox.getGlobalBounds().height - 33.f);

	mapBox = thor::Shapes::roundedRect(
		{ static_cast<float>(settingsData.screenW) * twoThirds - 5, static_cast<float>(settingsData.screenH) * .75f - 5 },
		4.f,
		sf::Color::Transparent,
		2.f,
		sf::Color(197, 239, 247, 255)
	);
	mapBox.setPosition(3.f, 3.f);

	statsBox = thor::Shapes::roundedRect(
		{ static_cast<float>(settingsData.screenW) * oneThird - 7, static_cast<float>(settingsData.screenH) * oneThird - 7 },
		4.f,
		sf::Color::Transparent,
		2.f,
		sf::Color(197, 239, 247, 255)
	);
	statsBox.setPosition(static_cast<float>(settingsData.screenW) * twoThirds + 4, static_cast<float>(settingsData.screenH) * twoThirds + 4);
}

void Game::registerComponents()
{
	// current limit: 32 components
	// no. of registered components: 29
	coordinator.registerComponent<ecs::EntityType>();
	coordinator.registerComponent<ecs::SpriteComponent>();
	coordinator.registerComponent<ecs::ClassName>();
	coordinator.registerComponent<ecs::Name>();
	coordinator.registerComponent<ecs::XP>();
	coordinator.registerComponent<ecs::Level>();
	coordinator.registerComponent<ecs::Inventory>();
	coordinator.registerComponent<ecs::Balance>();
	coordinator.registerComponent<ecs::Stats>();
	coordinator.registerComponent<ecs::LevelUpStats>();
	coordinator.registerComponent<ecs::Status>();
	coordinator.registerComponent<ecs::Velocity>();
	coordinator.registerComponent<ecs::Depth>();
	coordinator.registerComponent<ecs::TwoHanded>();
	coordinator.registerComponent<ecs::DamageMulti>();
	coordinator.registerComponent<ecs::BuyPrice>();
	coordinator.registerComponent<ecs::SellPrice>();
	coordinator.registerComponent<ecs::Equippable>();
	coordinator.registerComponent<ecs::WeaponEffects>();
	coordinator.registerComponent<ecs::LegendaryEffects>();
	coordinator.registerComponent<ecs::Description>();
	coordinator.registerComponent<ecs::ProtectionMulti>();
	coordinator.registerComponent<ecs::ArmorWeakness>();
	coordinator.registerComponent<ecs::EffectStrength>();
	coordinator.registerComponent<ecs::Tier>();
	coordinator.registerComponent<ecs::PotionType>();
	coordinator.registerComponent<ecs::Equipped>();
	coordinator.registerComponent<ecs::WeaponType>();
	coordinator.registerComponent<ecs::IsLegendary>();
}

int Game::load(const std::string& name)
{
	std::string filePath = "saves/" + name + ".json";
	if (std::filesystem::exists(filePath.c_str())) { // make sure the file exists
		std::fstream is(filePath.c_str());

		// rehash the save file and compare it to the old save file
		std::string rawData;
		std::string line;
		while (std::getline(is, line))
		{
			rawData += line;
		}
		is.close();

		std::string hashedData = picosha2::hash256_hex_string(rawData);
		std::string oldHashedData;

		// create unique id for the hash in order to find it after the game is closed. Set to 6 chars long for now unless I find I need more
		std::string hashID = picosha2::hash256_hex_string(name);
		hashID.resize(6);

		std::string hashedFilePath = "resources/sprites/" + hashID + ".png";

		std::fstream hIs;
		hIs.open(hashedFilePath.c_str());
		hIs >> oldHashedData;
		hIs.close();

		// compare hashes
		if (hashedData == oldHashedData)
		{
			std::fstream ias(filePath.c_str());
			// if equal load save
			cereal::JSONInputArchive iarchive(ias);
			iarchive(CEREAL_NVP(settingsData), CEREAL_NVP(archiveData));
			updateBorderColor();
			player = archiveData.loadPlayer();
			// reset and fill autocomplete
			autoComplete = std::make_shared<autoc::Node>();
			for (const auto& i : acWordList)
				autoc::insert(&autoComplete, i);

			return 1;
		}
		else
		{
			// maybe delete the files here would be kinda funny 
			return -1;
		}
	}
	return 0;
}

void Game::save(const std::string& name)
{
	std::string filePath = "saves/" + name + ".json";

	// ----------------------------------------------------------------------------------------------------------------
	// WRITING JSON DATA TO FILE

	std::ofstream os;
	os.open(filePath.c_str());
	if (os.is_open()) {
		cereal::JSONOutputArchive oarchive(os);
		archiveData.savePlayer(player);
		oarchive(CEREAL_NVP(settingsData), CEREAL_NVP(archiveData));
	}
	else throw std::runtime_error("Couldn't open or create " + filePath);

	// WRITING JSON DATA TO FILE
	// ----------------------------------------------------------------------------------------------------------------


	// ----------------------------------------------------------------------------------------------------------------
	// HASHING DATA

	// get written data in .json and convert to 1 string
	std::string rawData;
	std::fstream is;
	is.open(filePath.c_str());
	if (is.is_open()) {
		std::string line;
		while (std::getline(is, line))
		{
			rawData += line;
		}
		is.close();
	}
	else throw std::runtime_error("Couldn't open " + filePath);

	// convert string to SHA2-256 hash value

	// check if there is already a save with this filename
	// if no save, create a new hash file with a new hashCounter
	std::string hashID = picosha2::hash256_hex_string(name);
	hashID.resize(6);

	std::ofstream hOs;
	std::string hashPath = "resources/sprites/" + hashID + ".png";
	hOs.open(hashPath.c_str());

	if (hOs.is_open()) {
		// calculate hashed string
		std::string hashedData = picosha2::hash256_hex_string(rawData);
		// insert hashed string into file
		hOs << hashedData;
		hOs.close();
	}
	else throw std::runtime_error("Failed to save data. This corrupted your save file lol L");

	// HASHING DATA
	// ----------------------------------------------------------------------------------------------------------------

	if (settingsData.saves.find(name) == settingsData.saves.end())
		settingsData.saves.insert(name);
}

ecs::Entity Game::createEntity()
{
	return coordinator.createEntity();
}

void Game::updateBounds()
{
	inputBoxBounds = { static_cast<float>(settingsData.screenW) * twoThirds + 11, static_cast<float>(settingsData.screenH) * twoThirds - 38.f, static_cast<float>(settingsData.screenW) * oneThird - 21, 24.f };
	displayBoxBounds = { 3.f, static_cast<float>(settingsData.screenH) * .75f + 4, static_cast<float>(settingsData.screenW) * twoThirds - 5, static_cast<float>(settingsData.screenH) * .25f - 6 };
	outputBoxBounds = { static_cast<float>(settingsData.screenW) * twoThirds + 4, 3.f, static_cast<float>(settingsData.screenW) * oneThird - 7, static_cast<float>(settingsData.screenH) * twoThirds - 5 };
	mapBoxBounds = { 3.f, 3.f, static_cast<float>(settingsData.screenW) * twoThirds - 5, static_cast<float>(settingsData.screenH) * .75f - 5 };
	statsBoxBounds = { static_cast<float>(settingsData.screenW) * twoThirds + 4, static_cast<float>(settingsData.screenH) * twoThirds + 4, static_cast<float>(settingsData.screenW) * oneThird - 7, static_cast<float>(settingsData.screenH) * oneThird - 7 };
}

void Game::updateBorderColor()
{
	displayBox.setOutlineColor(settingsData.borderColor);
	outputBox.setOutlineColor(settingsData.borderColor);
	mapBox.setOutlineColor(settingsData.borderColor);
	statsBox.setOutlineColor(settingsData.borderColor);
	inputBox.setOutlineColor(settingsData.borderColor);
}

void Game::handleInput()
{
	sf::Event event;

	deltaTime = clock.restart().asSeconds();
	if (printFps) {
		static uint64_t fpsCounter = 0;
		if (fpsCounter++ % 600 == 0) {
			int fps = 1.f / deltaTime;
			printm("FPS: " + std::to_string(fps));
		}
	}

	while (window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			confirmExit();
			break;
		case sf::Event::KeyPressed:
			if (!gettingText || event.key.code == sf::Keyboard::Escape || event.key.code == sf::Keyboard::Enter || event.key.code == sf::Keyboard::Backspace || event.key.code == sf::Keyboard::Tab)
				inputManager.pressKey(event.key.code);
			break;
		case sf::Event::TextEntered:
			if (gettingText && event.text.unicode != 8 && event.text.unicode != 13 && event.text.unicode != 9) { // filter out backspace, return, and tab keys (this uses unicode decimal value)
				inputText.push_back(static_cast<char>(event.text.unicode));
				inputTextDrawable.set('>' + inputText);
			}
			break;
		case sf::Event::KeyReleased:
			inputManager.releaseKey(event.key.code);
			break;
		case sf::Event::MouseButtonPressed:
			inputManager.pressKey(event.mouseButton.button);
			break;
		case sf::Event::MouseButtonReleased:
			inputManager.releaseKey(event.mouseButton.button);
			break;
		case sf::Event::Resized:
			settingsData.screenW = event.size.width;
			settingsData.screenH = event.size.height;
			updateBounds();
			break;
		case sf::Event::MouseMoved:
			inputManager.setMouseCoords(static_cast<float>(event.mouseMove.x), static_cast<float>(event.mouseMove.y));
			break;
		case sf::Event::MouseWheelMoved:
		{
			// check if within outputbox bounds && if there is enough text on the screen to scroll
			float endPos = outputManager.getLastTextBounds().top + outputManager.getLastTextBounds().height * 2.f;
			if (outputBoxBounds.contains((float)event.mouseWheel.x, (float)event.mouseWheel.y) &&
				endPos > 720) 
			{
				float delta = event.mouseWheel.delta * deltaTime * 20000.0f;
				outputManager.moveView(-delta);
				float viewCenterY = outputManager.getView().getCenter().y;
				float halfViewY = outputManager.getView().getSize().y / 2.0f;
				float viewTop = viewCenterY - halfViewY;
				float viewBottom = viewCenterY + halfViewY;

				float firstTextY = outputManager.getFirstTextPos().y;

				if (viewTop < firstTextY)
				{
					outputManager.moveView(firstTextY - viewTop);
					break;
				}
				
				if (viewBottom > endPos && endPos > 480)
				{
					outputManager.moveView(endPos - viewBottom);
				}

			}
			break;
		}
		default:
			break;
		}

		if (inputManager.isKeyPressed(sf::Keyboard::Enter))
		{
			if (gettingText)
			{
				// prevent the invalid command error msg from displaying when an empty string is ran
				if (!inputText.empty()) {
					handleInputLogic(inputText);
					inputText.clear();
				}
				inputTextDrawable.set("");
			}
			else {
				inputTextDrawable.set('>');
			}
			gettingText = !gettingText;
		}
		else if (inputManager.isKeyPressed(sf::Keyboard::Escape))
		{
			gettingText = false;
			inputText.clear();
			inputTextDrawable.set("");
		}
		else if (inputManager.isKeyPressed(sf::Keyboard::Tab) && gettingText)
		{
			// get the word that is currently being typed
			std::string word;
			int lastSpace = 0;
			for (int i = inputText.size(); i > 0; i--)
			{
				if (inputText.at(i - 1) == ' ') {
					lastSpace = i;
					break;
				}
			}
			word = inputText.substr(lastSpace, std::string::npos);

			// currently only grabbing the first word to autocomplete, should be improved on later to give options for other words to tab to
			std::vector completedWords = autoc::autocomplete(autoComplete, word);
			if (!completedWords.empty()) // only change the word if there is something to correct to
				inputText += completedWords[0];

			inputTextDrawable.set('>' + inputText);
			break;
		}
		else if (inputManager.isKeyPressed(sf::Mouse::Left))
		{
			if (inputBoxBounds.contains(inputManager.getMouseCoords()))
			{
				if (!gettingText) inputTextDrawable.set('>');
				gettingText = true;
			}
		}
		else if (inputManager.isKeyPressed(sf::Mouse::Right))
		{
		}
		else if (inputManager.isKeyPressed(sf::Keyboard::F11))
		{
			//settingsData.screenW = 1920;
			//settingsData.screenH = 1080;
			if (settingsData.windowStyle == sf::Style::Default) {
				settingsData.windowStyle = sf::Style::Fullscreen;
			}
			else {
				settingsData.windowStyle = sf::Style::Default;
			}
			window.create(sf::VideoMode(settingsData.screenW, settingsData.screenH), "JordunRPG", settingsData.windowStyle, contextSettings);
			updateBounds();
		}
		else if (inputManager.isKeyPressed(sf::Keyboard::Backspace))
		{
			// keep empty, necessary to fix backspacing
		}
		else if (inputManager.isKeyDown(sf::Keyboard::Backspace) && gettingText && inputText.size() > 0)
		{
			inputText.pop_back();
			inputTextDrawable.set('>' + inputText);
		}

		inputManager.update();
	}
}

void Game::handleInputLogic(const std::string& str)
{
	std::vector<std::string> args;

	// convert string to lowercase and split into args for proper comparison
	std::string word;
	for (const auto& i : str)
	{
		if (i == ' ' || i == ',')
		{
			if (!word.empty()) { // make sure we arent pushing back empty string
				args.push_back(word);
				word.clear();
			}
		}
		else word += tolower(i);
	}
	if (!word.empty())
		args.push_back(word);

	// TODO: FIX THIS
	args.resize(10, ""); // really shitty way to prevent out of bounds reference (literally just making it big enough where i cant fuck up and grab anything nonexistent)

	// main help menu
	if (args[0] == "help" || args[0] == "?")
	{
		outputManager.print("Help Menu:\n\n", textColor, textSize + 8, sf::Text::Style::Bold, textFont);
		if (args[1].empty()) // Main help menu (lists options)
		{																							// Use\"help [prefix]\" to get arguments for that prefix.\n
			printm("**COMMANDS ARE NOT CASE SENSITIVE**\n\nUse \"help [page number]\" to list prefixes of the specified category.\nArguments listed in <> are required; arguments listed in [] are optional.\nArguments with * are dependent on each other (i.e. if one argument is used, the other must also be used).\nThe help menu does not give information on commands; for more details run the desired command without arguments.\n\n1. Settings/Customization commands\n2. Miscellaneous commands\nMore commands coming...");
			return;
		}
		else if (args[1] == "1") // Settings/Customization commands
		{
			outputManager.print("Settings/Customization Command Prefixes:\n", textColor, textSize + 4, textStyle, textFont);
			printm("borders\ntext\ndefine");
			return;
		}
		else if (args[1] == "2") // Miscellaneous commands (always keep this at the bottom of the list
		{
			outputManager.print("Miscellaneous Command Prefixes:\n", textColor, textSize + 4, textStyle, textFont);
			printm("fps");
		}
		else {
			printe("You did not input a valid argument!");
			return;
		}
		return;
	}
	// display fps
	else if (args[0] == "fps")
	{
		printFps = !printFps;
		return;
	}
	// clear output
	else if (args[0] == "clear" || args[0] == "cls")
	{
		outputManager.clear();
		return;
	}
	// customize borders
	else if (args[0] == "borders") // borders formatting options
	{
		if (args[1] == "color")
		{
			if (args[2] == "rgba")
			{
				settingsData.borderColor = sf::Color(std::stoi(args[3]), std::stoi(args[4]), std::stoi(args[5]), std::stoi(args[6]));
				updateBorderColor();
				printm("Border color has been set to r: " + args[3] + " g : " + args[4] + " b : " + args[5] + " a : " + args[6]);
				return;
			}
			else if (args[2] == "rgb")
			{
				settingsData.borderColor = sf::Color(std::stoi(args[3]), std::stoi(args[4]), std::stoi(args[5]), 255);
				updateBorderColor();
				printm("Border color has been set to r: " + args[3] + " g : " + args[4] + " b : " + args[5] + " a: 255");
				return;
			}
			else if (args[2] == "list")
			{
				printm("Your defined colors are:");
				for (const auto& i : settingsData.colorMap)
				{
					printm(i.first);
				}
				return;
			}
			else if (!args[2].empty())
			{
				if (settingsData.colorMap.find(args[2]) != settingsData.colorMap.end())
				{
					settingsData.borderColor = settingsData.colorMap.at(args[2]);
					updateBorderColor();
					printm("Border color has been set to " + args[2]);
					return;
				}
				else
				{
					printe(args[2] + " is not a valid argument or color!");
					printm("Your defined colors are: ");
					for (const auto& i : settingsData.colorMap)
					{
						printm(i.first);
					}
					return;
				}
			}
			else // explain how to format command
				printm("The \"borders color\" command takes rgb(a) colors between 0-255 with the format \"borders color rgb[a*] <r> <g> <b> [a*]\".\nYou can also input defined color names with the format \"borders color <color>\". See \"define color\" to define a custom color and \"color list\" to list your defined colors.");
			return;
		}
		else
		{
			printm("Commands with prefix \"borders\":\n\ncolor\n");
		}
		return;
	}
	// customize text
	else if (args[0] == "text") // text formatting options
	{
		if (args[1] == "color")
		{
			if (args[2] == "rgba")
			{
				settingsData.textColor = sf::Color(std::stoi(args[3]), std::stoi(args[4]), std::stoi(args[5]), std::stoi(args[6]));
				printm("Text color has been set to r: " + args[3] + " g : " + args[4] + " b : " + args[5] + " a : " + args[6]);
				return;
			}
			else if (args[2] == "rgb")
			{
				settingsData.textColor = sf::Color(std::stoi(args[3]), std::stoi(args[4]), std::stoi(args[5]), 255);
				printm("Text color has been set to r: " + args[3] + " g : " + args[4] + " b : " + args[5] + " a: 255");
				return;
			}
			else if (args[2] == "list")
			{
				printm("Your defined colors are:");
				for (const auto& i : settingsData.colorMap)
				{
					printm(i.first);
				}
				return;
			}
			else if (!args[2].empty())
			{
				if (settingsData.colorMap.find(args[2]) != settingsData.colorMap.end())
				{
					settingsData.textColor = settingsData.colorMap.at(args[2]);
					printm("Text color has been set to " + args[2]);
					return;
				}
				else
				{
					printe(args[2] + " is not a valid argument or color!");
					printm("Your defined colors are: ");
					for (const auto& i : settingsData.colorMap)
					{
						printm(i.first);
					}
					return;
				}
			}
			else {	// explain how to format command
				printm("The \"text color\" command takes rgb(a) colors between 0-255 with the format \"text color rgb[a*] <r> <g> <b> [a*]\".\nYou can also input defined color names with the format \"borders color <color>\". See \"define color\" to define a custom color and \"color list\" to list your defined colors.");
				return;
			}
		}
		else if (args[1] == "size")
		{
			if (!args[2].empty())
			{
				settingsData.textSize = std::stoi(args[2]);
				printm("Text size has been set to " + args[2]);
				return;
			}
			else {
				printe("The text size is a required value.\n\"text size <int>\"");
				return;
			}

		}
		else if (args[1] == "style")
		{
			if (args[2] == "default" || args[2] == "reset" || args[2] == "regular")
			{
				settingsData.textStyle = sf::Text::Style::Regular;
				printm("Text font has been reset to default");
			}
			if (args[2] == "bold") {
				settingsData.textStyle = sf::Text::Style::Bold;
				printm("Text font has been set to bold");
			}
			else if (args[2] == "underlined" || args[2] == "underline")
			{
				settingsData.textStyle = sf::Text::Style::Underlined;
				printm("Text font has been set to underlined");
			}
			else if (!args[2].empty())
			{
				printe("You did not give a proper text style value. The currently existing text styles are:\nDefault/Regular\nBold\nUnderlined");
			}
			else
			{
				printm("You can set the text style using \"text style <style>\". The currently existing text styles are:\nDefault/Regular\nBold\nUnderlined");
			}
			return;
		}
		else if (args[1] == "font")
		{
			if (args[2] == "unicode") {
				settingsData.textFont = Fonts::unicode;
				printm("Text font has been set to Unicode");
				return;
			}
			else if (args[2] == "lato") {
				settingsData.textFont = Fonts::lato;
				printm("Text font has been set to Lato");
				return;
			}
			else if (!args[2].empty()) {
				printe("You did not give a proper font value. The currently existing fonts are:\nUnicode\nLato\n\nMore fonts & user-defined fonts will be added in the future!");
				return;
			}
			else {
				printm("You can change the font of the displayed text using \"text font <font>\". The currently existing fonts are:\nUnicode\nLato\n\nMore fonts & user-defined fonts will be added in the future!");
			}
		}
		else {
			printm("Currently existing commands with prefix \"text\":\n\ncolor\nsize\nstyle\nfont");
		}
		return;
	}
	// define custom colors
	else if (args[0] == "define") // user custom defined things
	{
		if (args[1] == "color")
		{
			if (args[2].empty()) // if they didn't input anything explain how color definition works
			{
				printm("You can define your own custom color using the format\n\"define color <name> <r> <g> <b> [a]\".\nRGBA values must be between 0-255 (any number higher will roll over to 1 (i.e. num % 255)).\nThis allows you to reference your own color in any other command using the name you specified. To overwrite a previous color, simply call the same command again with the same name. Failing to follow the proper format will result in incorrect coloring.");
			}
			else
			{
				settingsData.colorMap.insert_or_assign(args[2], sf::Color(std::stoi(args[3]), std::stoi(args[4]), std::stoi(args[5]), args[6].empty() ? 255 : std::stoi(args[6])));
				insertACWord(args[2]);
				printm("Created new color named " + args[2] + " with r:" + args[3] + " g:" + args[4] + " b:" + args[5] + " a:" + (args[6].empty() ? "255" : args[6]));
			}
			return;
		}
		else {
			printm("Commands with prefix \"define\":\n\ncolor");
		}
		return;
	}
	// load game
	else if (args[0] == "load")
	{
		if (args[1].empty())
		{
			printm("You can load saves using the \"load <save name>\" command.");
			if (!settingsData.saves.empty()) {
				printm("Your currently existing saves are:\n");
				for (const auto& i : settingsData.saves)
				{
					printm(i);
				}
				return;
			}
			else
			{
				printm("You do not have any existing saves.");
			}
			return;
		}
		else
		{
			int result = load(args[1]);
			if (result == 0)
			{
				printe(args[1] + " is not a valid save name!");
				printm("Your currently existing saves are:\n");
				for (const auto& i : settingsData.saves)
				{
					printm(i);
				}
				return;
			}
			else if (result == 1)
			{
				printm("Successfully loaded save \"" + args[1] + "\"");
				return;
			}
			else if (result == -1)
			{
				printe("Your dumbass fucked with the save data. kys");
			}
		}
	}
	// save game
	else if (args[0] == "save")
	{
		if (args[1].empty())
		{
			printm("You can save game data using the \"save <save name>\" command.\nIf you write the name of an existing save it will overwrite the previous save.\nYour currently existing saves are:\n");
			for (const auto& i : settingsData.saves)
			{
				printm(i);
			}
			return;
		}
		else
		{
			save(args[1]);
			insertACWord(args[1]);
			printm("Successfully saved data to \"" + args[1] + "\"");
		}
	}
	else if (args[0] == "say" || args[0] == "print" || args[0] == "out")
	{
		std::string output = str;
		output.erase(0, args[0].length() + 1);
		printm(output);
		return;
	}
	else if (args[0] == "vsync")
	{
		settingsData.vsyncEnabled = !settingsData.vsyncEnabled;
		window.setVerticalSyncEnabled(settingsData.vsyncEnabled);
		printm("Vsync has been " + settingsData.vsyncEnabled ? "enabled" : "disabled");
		return;
	}
	else if (args[0] == "window")
	{
		if (args[1] == "resize" && !args[2].empty())
		{
			if (!args[3].empty()) {
				settingsData.screenW = std::stoi(args[2]);
				settingsData.screenH = std::stoi(args[3]);
				window.create(sf::VideoMode(settingsData.screenW, settingsData.screenH), "JordunRPG", settingsData.windowStyle, contextSettings);
				createBorders();
				outputManager.resetView(sf::FloatRect(0, 0, (oneThird - .01f) * settingsData.screenW, settingsData.screenH * (twoThirds - .06f)));
				updateBounds();
				inputTextDrawable.setPos({ inputBoxBounds.left + 2, inputBoxBounds.top + 6 });

				printm("The window has been resized to " + args[2] + "x" + args[3]);
				return;
			}
			else
			{
				int height = std::stoi(args[2]);
				int width = height * 16 / 9;
				settingsData.screenH = height;
				settingsData.screenW = width;
				window.create(sf::VideoMode(settingsData.screenW, settingsData.screenH), "JordunRPG", settingsData.windowStyle, contextSettings);
				createBorders();
				outputManager.resetView(sf::FloatRect(0, 0, (oneThird - .01f)* settingsData.screenW, settingsData.screenH* (twoThirds - .06f)));
				updateBounds();
				inputTextDrawable.setPos({ inputBoxBounds.left + 2, inputBoxBounds.top + 6 });

				printm("The window has been resized to " + std::to_string(width) + "x" + args[2]);
				return;
			}
		}
		else if (args[1] == "resize" && args[2].empty())
		{
			printm("You can set the screen width and screen height in pixels using \"window resize <screenW> <screenH>\" or \"window resize <screenH>\". If only the screen height is inputted, the screen width will be automatically generated based on a 16:9 ratio");
			return;
		}
		printm("Commands with prefix \"window\":\n\nresize");
		return;
	}
	else if (args[0] == "akira3k")
	{
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
		// force them to sub to akira3k
		ShellExecute(0, 0, L"https://www.youtube.com/channel/UCzhxJWV28CyQb00aOlpUbJA?sub_confirmation=1", 0, 0, SW_HIDE);
#else
		system("open https://www.youtube.com/channel/UCzhxJWV28CyQb00aOlpUbJA?sub_confirmation=1");
#endif
		return;
	}
	else if (args[0] == "exit" || args[0] == "quit")
	{
		confirmExit();
		return;
	}
	else
	{
		printe("You did not input a valid command. Run \"help\" to see commands.");
		return;
	}
}

// checks if a word already exists in the autocorrect dictionary. if not, it inserts it.
void Game::insertACWord(const std::string& word)
{
	// make sure it doesnt exist and then add it, else dont do anything
	if (acWordList.find(word) == acWordList.end())
	{
		acWordList.insert(word);
		autoc::insert(&autoComplete, word);
	}
}

void Game::printm(const std::string& str)
{
	outputManager.print(str, textColor, textSize, textStyle, textFont);
}

void Game::printe(const std::string& str)
{
	outputManager.printError(str, textSize, textFont);
}

void Game::drawBoxes()
{
	window.draw(displayBox);
	window.draw(inputBox);
	window.draw(outputBox);
	window.draw(mapBox);
	window.draw(statsBox);
}

void Game::drawStats()
{
}

void Game::renderGame()
{
	window.clear();

	// draw outline boxes
	drawBoxes();

	// draw text output
	outputManager.draw(window);
	inputTextDrawable.draw(window);

	// draw stats


	// draw backpack

	// draw scene

	window.display();
}

void Game::confirmExit()
{
	if (settingsData.displayConfirmationOnExit) {
		const SDL_MessageBoxButtonData buttons[] = {
			{SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 0, "Confirm"},
			{SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 1, "Cancel"},
			{0, 2, "Disable"}
		};
		const SDL_MessageBoxColorScheme colorScheme = {
			{
				// background
				{255, 255, 255},
				// text
				{0, 0, 0},
				// button border
				{150, 150, 150},
				// button background
				{255, 255, 255},
				// button selected
				{200, 200, 200}
			}
		};
		const SDL_MessageBoxData messageBoxData = {
			SDL_MESSAGEBOX_WARNING,
			NULL,
			"EXIT CONFIRMATION",
			"Are you sure you want to exit?\n\nPress confirm to exit, cancel to return to the game, or disable to disable this prompt.",
			SDL_arraysize(buttons),
			buttons,
			&colorScheme
		};

		int buttonID;
		if (SDL_ShowMessageBox(&messageBoxData, &buttonID) < 0)
			throw std::runtime_error("Failed to display message box");
		else if (buttonID == 0)
			gameState = GameState::Exit;
		else if (buttonID == 2) {
			settingsData.displayConfirmationOnExit = false;
			// DECIDE WHAT TO CALL THIS COMMAND LATER
			printm("You have disabled the exit confirmation dialogue box. To reenable this, run the \"enable confirmation\" command. (get trolled idiot i havent even added this yet)");
		}
	}
	else
		gameState = GameState::Exit;
}
