#pragma once
#include <SFML/Graphics.hpp>
#include "Text.h"
#include <unordered_map>
#include <set>

#include "Serialization.h"

class SettingsData
{
public:
	SettingsData() = default;

public:
	unsigned int screenW = 1920;
	unsigned int screenH = 1080;
	bool vsyncEnabled = true;
	sf::Uint32 windowStyle = sf::Style::Default;

	sf::Color textColor = { 255, 255, 255, 255 };
	sf::Color borderColor = { 255, 255, 255, 255 };
	int textSize = 16;
	sf::Text::Style textStyle = sf::Text::Style::Regular;
	Fonts textFont = Fonts::unicode;
	std::unordered_map<std::string, sf::Color> colorMap;
	std::set<std::string> saves;
	std::unordered_map<std::string, int> hashMap;
	int hashCounter = 0;
	bool displayConfirmationOnExit = true;

	// ---------------------- SERIALIZATION ----------------------

public:
	template<class Archive>
	inline void serialize(Archive& archive)
	{
		archive(
			CEREAL_NVP(vsyncEnabled),
			CEREAL_NVP(screenW),
			CEREAL_NVP(screenH),
			CEREAL_NVP(windowStyle),
			CEREAL_NVP(textColor),
			CEREAL_NVP(borderColor),
			CEREAL_NVP(textSize),
			CEREAL_NVP(textStyle),
			CEREAL_NVP(textFont),
			CEREAL_NVP(colorMap),
			CEREAL_NVP(saves),
			CEREAL_NVP(displayConfirmationOnExit),
			cereal::make_nvp("hMap", hashMap), 
			cereal::make_nvp("hCounter", hashCounter));
	}

	// ---------------------- SERIALIZATION ----------------------
};