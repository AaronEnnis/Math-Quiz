#pragma once
#include "SFML/Graphics.hpp"
#include <string>

class Question
{
public:
	Question(std::string q, std::string c1, std::string c2, std::string c3, std::string c4, std::string ans);
	~Question();

	std::string answer;
	std::string choice1;
	std::string choice2;
	std::string choice3;
	std::string choice4;
	std::string question;
	sf::Text text;
	sf::Text choices[4];

	void draw(sf::RenderWindow &window);
	void MoveUp();
	void MoveDown();
	int GetPressedItem() { return selectedItemIndex; }
	void resetIndex();

private:
	int selectedItemIndex;
};

