#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

enum class Fonts {
    unicode = 0,
    lato = 1
};

enum class RotateDirection
{
    clockwise = 0,
    counterclockwise = 1
};

class Text {
private:
    sf::Font* lato;
    sf::Font* unicode;
    sf::Font* custom;
    sf::Text text;

public:
    Text() {}
    Text(sf::Font* lato, sf::Font* unicode, sf::Font* custom) : lato{ lato }, unicode{ unicode }, custom{ custom } {
        text.setFont(*this->unicode);
        text.setCharacterSize(24);
    }

    // DO NOT DELETE THE FONTS THEMSELVES
    ~Text() { lato = nullptr; unicode = nullptr; }
    
public:
    sf::Text& getText() { return text; }

    void font(int s){
        if (s == 0)
            text.setFont(*lato);
        else
            text.setFont(*unicode);
    }
    void font(Fonts s) {
        if (s == Fonts::lato)
            text.setFont(*lato);
        else if (s == Fonts::unicode)
            text.setFont(*unicode);
    }
    void set(char c) {
        text.setString(c);
    }
    void set(const std::string& s) {
        text.setString(s);
    }
    void set(const std::wstring& ws) {
        text.setString(sf::String(ws));
    }
    void size(int s) {
        text.setCharacterSize(s);
    }
    void setPos(const sf::Vector2f& pos)
    {
        text.setPosition(pos);
    }
    void rotate(RotateDirection r)
    {
        if (r == RotateDirection::clockwise)
            text.rotate(90);
        else
            text.rotate(-90);
    }
    void color(const sf::Color& c) {
        text.setFillColor(c);
    }
    void style(const sf::Text::Style& style) {
        text.setStyle(style);
    }
    void draw(sf::RenderWindow& window) {
        window.draw(text);
    }
};