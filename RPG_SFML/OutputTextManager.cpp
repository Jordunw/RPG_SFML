#include "OutputTextManager.h"

void OutputTextManager::draw(sf::RenderWindow& window)
{
	window.setView(view);
	for (auto i : text)
		i.draw(window);
	window.setView(window.getDefaultView());
}

void OutputTextManager::print(const std::wstring& str,
								sf::Color c,
								float size,
								sf::Text::Style style)
{
	text.emplace_back(&lato, &unicode, nullptr);
	text.back().set(str);
	text.back().color(c);
	text.back().style(style);
	text.back().size(size);

	for (int i = text.size(); i > 0; i--)
	{

	}

	for (int i = 0; i < text.size(); i++)
	{
		if (i != 0)
		{
			int length = text.at(i - 1).getText().getString().getSize() - 1;
			text.at(i).setPos(sf::Vector2f(0, (text.at(i - 1).getText().findCharacterPos(length).y + static_cast<float>(text.at(i - 1).getText().getGlobalBounds().height) + 10)));
		}
	}
}

void OutputTextManager::scroll(float dist)
{
}
