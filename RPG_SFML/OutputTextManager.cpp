#include "OutputTextManager.h"

void OutputTextManager::moveView(float distance)
{
	view.move({ 0, distance });
}

void OutputTextManager::init()
{
	if (!lato.loadFromFile("resources/fonts/Lato-Regular.ttf"))
	{
		throw std::runtime_error("Failed to load font Lato from \"resources/fonts/Lato-Regular.ttf\"");
	}
	if (!unicode.loadFromFile("resources/fonts/unifont-13.0.06.ttf"))
	{
		throw std::runtime_error("Failed to load font Unifont from \"resources/fonts/unifont-13.0.06.ttf\"");
	}
}

void OutputTextManager::resetView(const sf::FloatRect& rect)
{
	view.reset(rect);
}

void OutputTextManager::setViewport(const sf::FloatRect& rect)
{
	view.setViewport(rect);
}

void OutputTextManager::draw(sf::RenderWindow& window)
{
	window.setView(view);
	float viewHalfSize = view.getSize().y * .5f;
	float viewBottom = view.getCenter().y + viewHalfSize;
	float viewTop = view.getCenter().y - viewHalfSize;

	for (auto& i : textMap)
	{
		sf::FloatRect bounds = i.second.getText().getGlobalBounds();

		// only draw the text if it is within the viewport
		if (bounds.top + bounds.height > viewTop && bounds.top < viewBottom)
			i.second.draw(window);
	}

	window.setView(window.getDefaultView());
}

void OutputTextManager::print(const std::wstring str, sf::Font& font, const int size)
{
	//[b(29,93,246)u]text[]text[]text
}

void OutputTextManager::print(const std::wstring& str,
	const sf::Color& c,
	int size,
	unsigned int style,
	const Fonts& font)
{
	textMap.insert(std::pair<int, Text>(textCounter, { font == Fonts::unicode ? &unicode : &lato, str, c, size }));
	this->style(textMap.at(textCounter), style);

	// get the newly created sf::Text
	sf::Text& currentText = textMap.at(textCounter).getText();
	std::wstring wstr = str;

	float viewWidth = *screenW * .75f * oneThird;

	for (int j = 0; j < static_cast<int>(wstr.size()); j++)
	{
		static int space;
		if (wstr.at(j) == ' ') space = j;
		else if (currentText.findCharacterPos(j).x > viewWidth)
		{
			wstr.at(space) = '\n';
			currentText.setString(wstr);
		}
	}

	if (textCounter > 0)
	{
		sf::Text& prevText = textMap.at(textCounter - 1).getText();
		float prevTextBottom = prevText.getGlobalBounds().top + prevText.getGlobalBounds().height;

		textMap.at(textCounter).setPos({ 0, prevTextBottom + 5.f }); // padding (will always be 5px below the last text

		sf::FloatRect textBounds = currentText.getGlobalBounds();
		float viewBottom = view.getCenter().y + view.getSize().y * .5f;
		float textBottom = textBounds.top + textBounds.height;

		if (textBottom > viewBottom)
			moveView(textBottom - viewBottom); // set the view to the bottom of the output
	}

	if (textCounter > 74)
	{
		textMap.erase(textCounter - 75);
	}

	textCounter++;
}

//void OutputTextManager::print(const std::string& str,
//	const sf::Color& c,
//	const int& size,
//	const unsigned int& style,
//	const Fonts& font)
//{
//	textMap.insert(std::pair<int, Text>(textCounter, { font == Fonts::unicode ? &unicode : &lato, str, c, size }));
//	this->style(textMap.at(textCounter), style);
//
//	// get the newly created sf::Text
//	sf::Text& currentText = textMap.at(textCounter).getText();
//	std::string wstr = str;
//
//	float viewWidth = *screenW * .75f * oneThird;
//
//	for (int j = 0; j < static_cast<int>(wstr.size()); j++)
//	{
//		static int space;
//		if (wstr.at(j) == ' ') space = j;
//		else if (currentText.findCharacterPos(j).x > viewWidth)
//		{
//			wstr.at(space) = '\n';
//			currentText.setString(wstr);
//		}
//	}
//
//	if (textCounter > 0)
//	{
//		sf::Text& prevText = textMap.at(textCounter - 1).getText();
//		float prevTextBottom = prevText.getGlobalBounds().top + prevText.getGlobalBounds().height;
//
//		textMap.at(textCounter).setPos({ 0, prevTextBottom + 5.f }); // padding (will always be 5px below the last text
//
//		sf::FloatRect textBounds = currentText.getGlobalBounds();
//		float viewBottom = view.getCenter().y + view.getSize().y / 2.f;
//		float textBottom = textBounds.top + textBounds.height;
//
//		if (textBottom > viewBottom)
//			moveView(textBottom - viewBottom); // set the view to the bottom of the output
//	}
//
//	if (textCounter > 74)
//	{
//		textMap.erase(textCounter - 75);
//	}
//
//	textCounter++;
//}

void OutputTextManager::clear()
{
	if (textMap.size() > 0) {
		view.move({ 0, -(view.getCenter().y - view.getSize().y * .5f) });
		textMap.clear();
		textCounter = 0;
	}
}

void OutputTextManager::style(Text& text, unsigned int style)
{
	if (style & 1)
		text.style(sf::Text::Style::Bold);
	if (style & 2)
		text.style(sf::Text::Style::Italic);
	if (style & 4)
		text.style(sf::Text::Style::Underlined);
	if (style & 8)
		text.style(sf::Text::Style::StrikeThrough);
}
