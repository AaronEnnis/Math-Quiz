#include "Question.h"

Question::Question()
{
	if (!font.loadFromFile("arial.ttf"))
	{
		// handle error
	}
	
	text.setFont(font);
	text.setFillColor(sf::Color::Red);
}

void Question::draw(sf::RenderWindow &window)
{
	window.draw(text);
}




