/*
Aaron Ennis
C00190504
*/
#include <stdlib.h>
#include "SFML/Graphics.hpp"
#include "Menu.h"
#include "Question.h"
#include <iostream>
#include <fstream>
#include <string>

int main()
{
	std::vector <Question> question(10);
	std::ifstream myfile("questions.txt");
	std::string line;

	question[0].answer = 4;
	question[1].answer = 8;
	question[2].answer = 10;
	question[3].answer = 4;
	question[4].answer = 6;
	question[5].answer = 11;
	question[6].answer = 6;
	question[7].answer = 11;
	question[8].answer = 3;
	question[9].answer = 4;
	
	int score = 0;
	bool play = false;

	int wrongAnswer1 = rand() % 13 + 1;
	int wrongAnswer2 = rand() % 13 + 1;
	int wrongAnswer3 = rand() % 13 + 1;

	if (myfile.is_open())
	{
		int i = 0;
		float j = 0;
		while (getline(myfile, line))
		{
			question[i].text.setString(line);
			question[i].text.setPosition(sf::Vector2f(50, 50 + j));
			i++;
			j = j + 50;
		}
		myfile.close();
	}

	else {
		std::cout << "Unable to open file";
	}


	sf::RenderWindow window(sf::VideoMode(600, 600), "Quiz!");

	Menu menu(window.getSize().x, window.getSize().y);

	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::KeyReleased:
				switch (event.key.code)
				{
				case sf::Keyboard::Up:
					if (!play)
					{
						menu.MoveUp();
					}
					break;

				case sf::Keyboard::Down:
					if (!play)
					{
						menu.MoveDown();
					}
					break;

				case sf::Keyboard::Return:
					switch (menu.GetPressedItem())
					{
					case 0:
						score = 0;
						play = true;
						break;
					case 1:
						std::cout << "High Score = " << score << std::endl;
						break;
					case 2:
						window.close();
						break;
					}

					break;
				}

				break;
			case sf::Event::Closed:
				window.close();
				break;
			}
		}
		
		window.clear();
		if (!play)
		{
			menu.draw(window);
		}
		else
		{
			for (int i = 0; i < 10; i++)
			{
				question[i].draw(window);
			}
		}
		window.display();
	}
}