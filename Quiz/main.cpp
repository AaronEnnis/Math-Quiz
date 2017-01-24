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
#include <vector>

int main()
{
	std::vector <Question> questions;
	std::ifstream myfile("questions.txt");
	std::string line;

	sf::Font font;
	if (!font.loadFromFile("arial.ttf"))
	{
		// handle error
	}

	int score = 0;
	bool play = false;

	if (myfile.is_open())
	{
		int i = 1;
		int j = 0;
		std::string q;
		std::string c1;
		std::string c2;
		std::string c3;
		std::string c4;
		std::string answer;

		while (getline(myfile, line))
		{			
			if (i == 1)
			{
				q = line;
			}
			else if (i == 2)
			{
				c1 = line;
			}
			else if (i == 3)
			{
				c2 = line;
			}
			else if (i == 4)
			{
				c3 = line;
			}
			else if (i == 5)
			{
				c4 = line;
			}
			else if(i == 6)
			{
				answer = line;
				Question question(q, c1, c2, c3, c4, answer);				
				questions.push_back(question);
				questions[j].text.setFont(font);
				questions[j].text.setFillColor(sf::Color::Red);
				questions[j].text.setString(questions[j].question);
				questions[j].text.setPosition(sf::Vector2f(600 / 2, 600 / (MAX_NUMBER_OF_ITEMS + 1) * (j+1)));
				i = 0;
				j++;				
			}			
			i++;
		}

		for (unsigned i = 0; i < questions.size(); i++)
		{
			std::cout << questions.at(i).question << std::endl;
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
			for (int i = 0; i < questions.size(); i++)
			{
				questions.at(i).draw(window);
			}
			
		}
		window.display();
	}
}