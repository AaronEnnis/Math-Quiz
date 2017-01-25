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
#include <ctime>
#include <sstream>
#include <iomanip>
#pragma warning(disable:4996)

int myrandom(int i) { return std::rand() % i; }

int main()
{
	sf::Text highScores[5];
	std::vector <Question> questions;
	std::vector <std::string> scores;
	std::ifstream myfile("questions.txt");
	std::string line;
	sf::Text correct;
	sf::Text inCorrect;

	sf::Font font;
	if (!font.loadFromFile("kenyan coffee.ttf"))
	{
		// handle error
	}

	int score = 0;
	bool play = false;
	bool right;
	bool highScore = false;
	bool next = false;

	correct.setFont(font);				
	correct.setFillColor(sf::Color::Red);
	correct.setString("Correct!");
	correct.setCharacterSize(30);
	correct.setPosition(sf::Vector2f(500, 100));

	inCorrect.setFont(font);				
	inCorrect.setFillColor(sf::Color::Red);
	inCorrect.setString("Wrong!");
	inCorrect.setCharacterSize(30);
	inCorrect.setPosition(sf::Vector2f(500, 100));

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
				questions[j].text.setCharacterSize(60);
				questions[j].text.setPosition(sf::Vector2f(100,50));

				for (int k = 0; k < 4; k++)		//setting the values of the 4 choices
				{
					if (k == 0)
					{
						questions[j].choices[k].setFont(font);
						questions[j].choices[k].setFillColor(sf::Color::Red);
						questions[j].choices[k].setString(questions[j].choice1);
						questions[j].choices[k].setCharacterSize(60);
						questions[j].choices[k].setPosition(sf::Vector2f(350, 50));
					}
					else if (k == 1)
					{
						questions[j].choices[k].setFont(font);
						questions[j].choices[k].setFillColor(sf::Color::White);
						questions[j].choices[k].setString(questions[j].choice2);
						questions[j].choices[k].setCharacterSize(60);
						questions[j].choices[k].setPosition(sf::Vector2f(350, 150));
					}
					else if (k == 2)
					{
						questions[j].choices[k].setFont(font);
						questions[j].choices[k].setFillColor(sf::Color::White);
						questions[j].choices[k].setString(questions[j].choice3);
						questions[j].choices[k].setCharacterSize(60);
						questions[j].choices[k].setPosition(sf::Vector2f(350, 250));
					}
					else if (k == 3)
					{
						questions[j].choices[k].setFont(font);
						questions[j].choices[k].setFillColor(sf::Color::White);
						questions[j].choices[k].setString(questions[j].choice4);
						questions[j].choices[k].setCharacterSize(60);
						questions[j].choices[k].setPosition(sf::Vector2f(350, 350));
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
			std::ifstream myfile("highScore.txt");
			switch (event.type)
			{
			case sf::Event::KeyReleased:
				switch (event.key.code)
				{
				case sf::Keyboard::Escape:
					highScore = false;
					next = false;
					break;
				case sf::Keyboard::Up:
					if (!play)
					{
						menu.MoveUp();
					}
					else
					{
						if (!next)
						{
							questions[loop].MoveUp();
						}
					}
					break;

				case sf::Keyboard::Down:
					if (!play)
					{
						menu.MoveDown();						
					}
					else
					{
						if (!next)
						{
							questions[loop].MoveDown();
						}
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

							highScore = true;

							if (myfile.is_open())
							{
								scores.clear();

								while (getline(myfile, line))
								{
									scores.push_back(line);
								}

								myfile.close();

								sort(scores.rbegin(), scores.rend());

								for (int i = 0; i < 5; i++)
								{
									highScores[i].setFont(font);				//setting the high scores to text
									highScores[i].setFillColor(sf::Color::Red);

									if (i == 0)
									{
										highScores[i].setString(scores[i]);
										highScores[i].setCharacterSize(30);
										highScores[i].setPosition(sf::Vector2f(50, 50));
									}
									else if (i == 1)
									{
										highScores[i].setString(scores[i]);
										highScores[i].setCharacterSize(30);
										highScores[i].setPosition(sf::Vector2f(50, 100));
									}
									else if (i == 2)
									{
										highScores[i].setString(scores[i]);
										highScores[i].setCharacterSize(30);
										highScores[i].setPosition(sf::Vector2f(50, 150));
									}
									else if (i == 3)
									{
										highScores[i].setString(scores[i]);
										highScores[i].setCharacterSize(30);
										highScores[i].setPosition(sf::Vector2f(50, 200));
									}
									else if (i == 4)
									{
										highScores[i].setString(scores[i]);
										highScores[i].setCharacterSize(30);
										highScores[i].setPosition(sf::Vector2f(50, 250));
									}
									
								}
							}

							else {
								std::cout << "Unable to open file";
							}

							break;
						case 2:
							window.close();
							break;
						}
					}
					else if(play && !next)
					{
						switch (questions[loop].GetPressedItem())
						{
						case 0:
							if (questions[loop].choice1==questions[loop].answer)
							{
								std::cout << "correct" << std::endl;
								questions[loop].resetIndex();
								score = score + 10;
								next = true;
								right = true;
							}
							else {
								std::cout << "wrong" << std::endl;
								questions[loop].resetIndex();
								next = true;
								right = false;
							}
							break;
						case 1:
							if (questions[loop].choice2 == questions[loop].answer)
							{
								std::cout << "correct" << std::endl;
								questions[loop].resetIndex();
								score = score + 10;
								next = true;
								right = true;
							}
							else {
								std::cout << "wrong" << std::endl;
								questions[loop].resetIndex();
								next = true;
								right = false;
							}
							break;
						case 2:
							if (questions[loop].choice3 == questions[loop].answer)
							{
								std::cout << "correct" << std::endl;
								questions[loop].resetIndex();
								score = score + 10;
								next = true;
								right = true;
							}
							else {
								std::cout << "wrong" << std::endl;
								questions[loop].resetIndex();
								next = true;
								right = false;
							}
							break;
						case 3:
							if (questions[loop].choice4 == questions[loop].answer)
							{
								std::cout << "correct" << std::endl;
								questions[loop].resetIndex();
								score = score + 10;
								next = true;
								right = true;
							}
							else {
								std::cout << "wrong" << std::endl;
								questions[loop].resetIndex();
								next = true;
								right = false;
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

			auto t = std::time(nullptr);
			auto tm = *std::localtime(&t);
			std::ostringstream oss;
			oss << std::put_time(&tm, "%d-%m-%Y %H-%M-%S");
			auto str = oss.str();
			std::ofstream myfile;
			myfile.open("highScore.txt", std::ios_base::app);
			myfile << "score: " << score << "   " << str << std::endl;
			myfile.close();
			std::cout << score << std::endl;
		}
		
		window.clear();
		if (!play && !highScore)
		{
			menu.draw(window);
		}
		if(play)
		{
			if (next)
			{
				if (right)
				{
					window.draw(correct);
				}
				else
				{
					window.draw(inCorrect);
				}
			}
			else 
			{
				questions.at(loop).draw(window);
			}

					
		}
		if (highScore)
		{
			for (int i = 0; i < 5; i++)
			{
				window.draw(highScores[i]);
			}
		}

		window.display();
	}
}