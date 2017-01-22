#pragma once
#include "SFML/Graphics.hpp"

class Question
{
public:
	Question();
	void draw(sf::RenderWindow &window);

	int answer;
	sf::Text text;
private:
	sf::Font font;
	
};

