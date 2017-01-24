#include "Question.h"

Question::Question(std::string q, std::string c1, std::string c2, std::string c3, std::string c4, std::string ans)
{
	question = q;
	choice1 = c1;
	choice2 = c2;
	choice3 = c3;
	choice4 = c4;
	answer = ans;
	
}
Question::~Question()
{
}

void Question::draw(sf::RenderWindow &window)
{
	window.draw(text);

}
