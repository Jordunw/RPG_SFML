#include "Game.h"

void Game::run()
{
	while (running)
	{
		deltaTime = clock.restart().asMilliseconds();
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
	initializeSettings();
	window.create(sf::VideoMode(screenW, screenH), "JordunRPG", 7U, contextSettings);
	window.setVerticalSyncEnabled(vsyncEnabled);
	createBorders();
	outputTextView.reset(sf::FloatRect(0, 0, (oneThird - .01f) * screenW, screenH * twoThirds));
	outputTextView.setViewport(sf::FloatRect(twoThirds + .01f, .015f, 0.3233f, twoThirds - .03f)); // to calculate w & h take the pixels of reset() and divide by width/height (so 5000/720 = 6.944)

	coordinator.init();
	registerComponents();
	loadText();

	for (int i = 0; i < 10; i++)
	{
		outputText.emplace_back(&lato, &unicode, &custom);
		outputText.at(i).size(16);
	}

	//outputText[0].set(L"This is a long string to test the ability to display over multiple lines as well as to see if the scrolling capabilities will work so I am making this incredibly long and repeating words and extending this as long as I can so that it covers enough area that it would be necessary to scroll to see all of the text within this string I am also going to make sure unicode characters work by doing stuff like \u2508and \u2500and hopefully these display unicode characters properly so I can make sure that unicode actually works in this text output format I am also going to put some \nnewlines\nhere\nto\nmake\nsure\nnewlines\nwork");
	//std::wstring tempString = outputText[0].getText().getString().toWideString();
	//int space = 0;
	//for (int i = 0; i < outputText[0].getText().getString().getSize(); i++)
	//{
	//	if (outputText[0].getText().getString().toWideString().at(i) == ' ')
	//		space = i;
	//	if (outputText[0].getText().findCharacterPos(i).x > 395)
	//	{
	//		tempString.at(space) = '\n';
	//		outputText[0].getText().setString(tempString);
	//	}
	//}

	outputText[0].set(L"test BING BING BING");
	outputText[1].set(L"TESTING AGAIN BING IBNG ");
	outputText[2].set(L"LOLFJDKSLGJKL:AJKW");
	outputText[3].set(L"Checking memory");
	outputText[4].set(L"Checking memory");
	outputText[5].set(L"Checking memory");
	outputText[6].set(L"Checking memory");
	outputText[7].set(L"Checking memory");
	outputText[8].set(L"Checking memory");
	outputText[9].set(L"Checking memory");
}

void Game::initializeSettings()
{
	std::fstream config;
	config.open("resources/settings.txt");

	if (config.is_open())
	{
		// if file is empty
		if (config.peek() == std::ifstream::traits_type::eof())
		{
			std::cout << "File \"settings.txt\" was empty!\nCreating a new file with default settings...\n\n";

			// write to config with default settings
			// 
			// set defaults
			return;
		}
		std::string cfg;
		std::string val;
		int setting = 0;
		int counter = 0;
		while (std::getline(config, cfg))
		{
			// grab settings
		}
		config.close();
	}
	else 
		throw std::runtime_error("Failed to open or create \"resources/settings.txt\"!File may be corrupted; create a new file of the same name to fix.");
}

void Game::createBorders()
{
	borders = Borders(sf::FloatRect(0, screenH * 3 / 4, screenW * 2 / 3, screenH / 4),
		sf::FloatRect(screenW * 2 / 3, 0, screenW / 3, screenH * 2 / 3),
		sf::FloatRect(0, 0, screenW * 2 / 3, screenH * 3 / 4),
		sf::FloatRect(screenW * 2 / 3, screenH * 2 / 3, screenW / 3, screenH / 3),
		-1,
		sf::Color::White);
}

void Game::loadText()
{
	if (!lato.loadFromFile("resources/fonts/Lato-Regular.ttf"))
	{
		throw std::runtime_error("Failed to load font \"Lato\" from \"resources/fonts/Lato-Regular.ttf\"");
	}
	if (!unicode.loadFromFile("resources/fonts/unifont-13.0.06.ttf"))
	{
		throw std::runtime_error("Failed to load font \"Lato\" from \"resources/fonts/unifont-13.0.06.ttf\"");
	}
	if (!custom.loadFromFile("C:\\Users\\Forest\\Desktop\\goated font.ttf"))
		throw std::runtime_error("Failed to load font \"goated font\" from \"C:\\Users\\Forest\\Desktop\\goated font.ttf\"");
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

ecs::Entity Game::createEntity()
{
	return coordinator.createEntity();
}

void Game::setTextPos(std::string key, sf::Vector2f pos)
{
	//textMap.at(key).setPos(pos);
}

void Game::setTextColor(std::string key, sf::Color color)
{
	//textMap.at(key).color(color);
}

void Game::setTextFont(std::string key, Fonts font)
{
	//textMap.at(key).font(font);
}

void Game::setTextStyle(std::string key, sf::Text::Style style)
{
	//textMap.at(key).style(style);
}

void Game::setText(std::string key, std::wstring text)
{
	//textMap.at(key).set(text);
}

void Game::rotateText(std::string key, RotateDirection r)
{
	//textMap.at(key).rotate(r);
}

void Game::drawText(std::string key)
{
	//textMap.at(key).draw(window);
}

void Game::handleInput()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			running = false;
			break;
		case sf::Event::KeyPressed:
			inputManager.pressKey(event.key.code);
			break;
		case sf::Event::KeyReleased:
			inputManager.releaseKey(event.key.code);
			break;
		case sf::Event::Resized:
			screenW = event.size.width;
			screenH = event.size.height;
			break;
		case sf::Event::MouseMoved:
			inputManager.setMouseCoords(static_cast<float>(event.mouseMove.x), static_cast<float>(event.mouseMove.y));
			break;
		case sf::Event::MouseButtonPressed:
			break;
		default:
			break;
		}
	}
}

void Game::renderGame()
{
	window.clear();

	// draw everything
	borders.draw(window);

	// draw text output
	outputManager.draw(window);

	window.display();
}
