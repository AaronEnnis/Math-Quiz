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
#include <algorithm>

int myrandom(int i) { return std::rand() % i; }

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

				questions[j].text.setFont(font);				//setting the question to text
				questions[j].text.setFillColor(sf::Color::White);
				questions[j].text.setString(questions[j].question);
				questions[j].text.setPosition(sf::Vector2f(200,50));

				for (int k = 0; k < 4; k++)		//setting the values of the 4 choices
				{
					if (k == 0)
					{
						questions[j].choices[k].setFont(font);
						questions[j].choices[k].setFillColor(sf::Color::Red);
						questions[j].choices[k].setString(questions[j].choice1);
						questions[j].choices[k].setPosition(sf::Vector2f(350, 50));
					}
					else if (k == 1)
					{
						questions[j].choices[k].setFont(font);
						questions[j].choices[k].setFillColor(sf::Color::White);
						questions[j].choices[k].setString(questions[j].choice2);
						questions[j].choices[k].setPosition(sf::Vector2f(350, 100));
					}
					else if (k == 2)
					{
						questions[j].choices[k].setFont(font);
						questions[j].choices[k].setFillColor(sf::Color::White);
						questions[j].choices[k].setString(questions[j].choice3);
						questions[j].choices[k].setPosition(sf::Vector2f(350, 150));
					}
					else if (k == 3)
					{
						questions[j].choices[k].setFont(font);
						questions[j].choices[k].setFillColor(sf::Color::White);
						questions[j].choices[k].setString(questions[j].choice4);
						questions[j].choices[k].setPosition(sf::Vector2f(350, 200));
					}
				}
				i = 0;
				j++;				
			}			
			i++;
		}

		myfile.close();
	}

	else {
		std::cout << "Unable to open file";
	}

	std::srand(unsigned(std::time(0)));
	random_shuffle(questions.begin(), questions.end(), myrandom);	//initially makes the question array random

	sf::RenderWindow window(sf::VideoMode(600, 600), "Quiz!");

	Menu menu(window.getSize().x, window.getSize().y);
	int loop = 0;
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
					else
					{
						questions[loop].MoveUp();
					}
					break;

				case sf::Keyboard::Down:
					if (!play)
					{
						menu.MoveDown();						
					}
					else
					{
						questions[loop].MoveDown();
					}
					break;

				case sf::Keyboard::Return:
					if (!play)
					{
						switch (menu.GetPressedItem())
						{
						case 0:

							std::srand(unsigned(std::time(0)));
							random_shuffle(questions.begin(), questions.end(), myrandom);
							score = 0;
							loop = 0;
							play = true;
							break;
						case 1:
							std::cout << "High Score = " << score << std::endl;
							break;
						case 2:
							window.close();
							break;
						}
					}
					else if(play)
					{
						switch (questions[loop].GetPressedItem())
						{
						case 0:
							if (questions[loop].choice1==questions[loop].answer)
							{
								std::cout << "correct" << std::endl;
							}
							else {
								std::cout << "wrong" << std::endl;
							}
							break;
						case 1:
							if (questions[loop].choice2 == questions[loop].answer)
							{
								std::cout << "correct" << std::endl;
							}
							else {
								std::cout << "wrong" << std::endl;
							}
							break;
						case 2:
							if (questions[loop].choice3 == questions[loop].answer)
							{
								std::cout << "correct" << std::endl;
							}
							else {
								std::cout << "wrong" << std::endl;
							}
							break;
						case 3:
							if (questions[loop].choice4 == questions[loop].answer)
							{
								std::cout << "correct" << std::endl;
							}
							else {
								std::cout << "wrong" << std::endl;
							}
							break;
						}
						loop++;
					}
					break;
				}

				break;
			case sf::Event::Closed:
				window.close();
				break;
			}
		}
		if (loop == 10)
		{
			loop = 0;
			play = false;
		}
		
		window.clear();
		if (!play)
		{
			menu.draw(window);
		}
		else
		{
			questions.at(loop).draw(window);		
		}
		window.display();
	}
}