#include "Question.h"

Question::Question(std::string q, std::string c1, std::string c2, std::string c3, std::string c4, std::string ans)
{
	question = q;
	choice1 = c1;
	choice2 = c2;
	choice3 = c3;
	choice4 = c4;
	answer = ans;
	selectedItemIndex = 0;
	
}
Question::~Question()
{
}

void Question::draw(sf::RenderWindow &window)
{
	window.draw(text);
	window.draw(choices[0]);
	window.draw(choices[1]);
	window.draw(choices[2]);
	window.draw(choices[3]);
}
void Question::MoveUp()
{
	if (selectedItemIndex - 1 >= 0)
	{
		choices[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex--;
		choices[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}

void Question::MoveDown()
{
	if (selectedItemIndex + 1 < 4)
	{
		choices[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex++;
		choices[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}
