#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/System/FileInputStream.hpp>
#include <iostream>

class Sprite {
private:
	sf::Texture texture;
	sf::Sprite sprite;

public:
	float x;
	float y;
	float width;
	float height;

public:
	Sprite() {}
	Sprite(const Sprite&) {}
	
	// undefined size constructor
	Sprite(std::string c, float x, float y, bool has_hitbox = true, bool smooth = false) {
		if (!texture.loadFromFile(c)) {
			std::cout << "Failed to load texture from file";
		}
		else {
			texture.setSmooth(smooth);
			sprite.setPosition(sf::Vector2f(x, y));
			sprite.setTexture(texture);
		}
		x = sprite.getGlobalBounds().left;
		y = sprite.getGlobalBounds().top;
		width = sprite.getGlobalBounds().width;
		height = sprite.getGlobalBounds().height;
	}

	// load a portion of the texture
	Sprite(std::string c, sf::IntRect rect, bool has_hitbox = true, bool smooth = false)
	{
		if (!texture.loadFromFile(c)) {
			std::cout << "Failed to load texture from file";
		}
		else {
			texture.setSmooth(smooth);
			sprite.setPosition(sf::Vector2f((float)rect.left, (float)rect.top));
			sprite.setTextureRect(sf::IntRect());
			sprite.setTexture(texture);
		}
		x = sprite.getGlobalBounds().left;
		y = sprite.getGlobalBounds().top;
		width = sprite.getGlobalBounds().width;
		height = sprite.getGlobalBounds().height;
	}

public:
	// draw sprite
	void draw(sf::RenderWindow &window) {
		window.draw(sprite);
	}
	// set pos
	void pos(float x, float y) {
		sprite.setPosition(sf::Vector2f(x, y));
	}
	// move the sprite from its current position
	void move(float x, float y){
		sprite.move(sf::Vector2f(x, y));
	}
	// absolute scaling
	void scale(float x, float y) {
		sprite.setScale(sf::Vector2f(x, y));
	}
	// relative scaling
	void relScale(float x, float y) {
		sprite.scale(sf::Vector2f(x, y));
	}
	// absolute rotation
	void setRotation(float r) {
		sprite.setRotation(r);
	}
	// relative rotation
	void rotate(float r) {
		sprite.rotate(r);
	}
	// change origin to the center of the sprite
	void centerOrigin() {
		sprite.setOrigin(sf::Vector2f(static_cast<float>(sprite.getTextureRect().width / 2), static_cast<float>(sprite.getTextureRect().height / 2)));
	}
	// change origin of the sprite to defined x and y
	void setOrigin(float x, float y) {
		sprite.setOrigin(sf::Vector2f(x, y));
	}
	// default opaque
	void color(int r, int g, int b, int a = 255) {
		sprite.setColor(sf::Color(r, g, b, a));
	}
	// get bounds of sprite
	float right() { return x + width; }
	float bottom() { return y + height; }

public:
	sf::Sprite getSprite() { return sprite; }
};