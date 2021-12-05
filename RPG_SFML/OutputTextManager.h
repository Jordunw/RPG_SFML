#pragma once
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "RichText.hpp"
#include <string>
#include <vector>
#include <map>
#include <queue>
#include <assert.h>
#include <memory>

enum class Fonts {
	unicode = 0,
	lato = 1
};

constexpr float oneThird = .3333333333333333333f;
constexpr float twoThirds = .6666666666666666667f;

class OutputTextManager
{
    public:
	OutputTextManager() : screenW{ nullptr }, screenH{ nullptr }{}
	OutputTextManager(std::shared_ptr<unsigned int> screenW, std::shared_ptr<unsigned int> screenH) : screenW{ screenW }, screenH{ screenH } {}
    
    private:
	sf::Font unicode, lato;
    
	sf::View view;
    
	std::map<int, sfe::RichText> textMap;
    
	int textCounter = 0;
    
	sf::Vector2f pos;
    
	std::shared_ptr<unsigned int> screenW;
	std::shared_ptr<unsigned int> screenH;
    
    public:
	void moveView(float distance);
    
	void init();
    
	const sf::View& getView() { return view; }
	sf::Font* getFont(Fonts font) { return font == Fonts::unicode ? &unicode : &lato; }
    
	sf::FloatRect getLastTextBounds() {
		if (textMap.size() > 0)
			return textMap.at(textCounter - 1).getGlobalBounds();
		return { 0,0,0,0 };
	}
	sf::Vector2f getFirstTextPos() {
		if (textCounter > 74)
			return textMap.at(textCounter - 74).getPosition();
		return { 0,0 };
	}
    
	void resetView(const sf::FloatRect& rect);
	void setViewport(const sf::FloatRect& rect);
    
	void draw(sf::RenderWindow& window);

	// adds text to buffer
	// works very similarly to minecraft color coding
	// all configs should come one after another and should begin with `
	// Note that order doesnt matter
	// `(000,000,000) to color
	// `b = bold
	// `s = strikethrough
	// `u = underline
	// `i = italics
	// `r = regular
	// example: "`b`(093,026,246)Bold Purple`d
	void print(const std::wstring& str, sf::Font& font, const int size);
	// add text to buffer
	// wstr
	//void print(const std::wstring& str,
    //           const sf::Color& c = sf::Color::White,
    //           int size = 16,
    //           unsigned int style = sf::Text::Style::Regular,
    //           const Fonts& font = Fonts::unicode);
	// str
	//void print(const std::string& str,
    //           const sf::Color& c = sf::Color::White,
    //           const int& size = 16,
    //           const unsigned int& style = sf::Text::Style::Regular,
    //           const Fonts& font = Fonts::unicode);
	// outputs bold red text. for use with error messages such as "this command does not exist"
	void printError(const std::wstring& str, int size, sf::Font& font) { print(str, font, size); }
    
	void clear(); // clear everything in the output
};