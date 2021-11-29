#pragma once
#include <SFML/Graphics.hpp>
#include "RichText.hpp"
#include <iostream>

enum class Fonts {
    unicode = 0,
    lato = 1
};

class Text
{
private:
    sfe::RichText text;

public:
    Text(){}
    Text(sf::Font& font,
        const std::wstring& wstr,
        const sf::Color& color,
        const sf::Text::Style& style,
        const int& size) 
    {
        text = sfe::RichText(font);
        text << style << color << wstr;
        text.setCharacterSize(size);
    }
    ~Text() {}

public:
    // returns a reference to the sfe::RichText
    sfe::RichText& getText() { 
        return text; 
    }
    // sets the font of the whole line
    void setFont(sf::Font& font) {
        text.setFont(font);
    }
    // sets the size of the whole line
    void setSize(int size) {
        text.setCharacterSize(size);
    }
    // adds a string of text with the defined color and style
    void addText(const std::wstring& str, const sf::Color& color, const sf::Text::Style& style) {
        text << color << style << str;
    }
    // sets the pos of the top left corner
    void setPos(const sf::Vector2f& pos) {
        text.setPosition(pos);
    }
    // rotates the line of text by degrees (positive clockwise, negative counterclockwise)
    void rotate(float degrees) {
        text.rotate(degrees);
    }
    // draws the text
    void draw(sf::RenderWindow& window) {
        window.draw(text);
    }
};