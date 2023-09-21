#include <iostream>
#include "FoodLog.h"

const float CALORIE_GOAL{ 1900 };

int main()
{
	FoodLog log;

	//std::cout << log.getTodaysDate() << '\n';

	log.readLog();
	bool windowShouldClose = false;
	char userSelection;
	while (!windowShouldClose)
	{
		//"game" loop
		log.getCalsProtein(CALORIE_GOAL);

		std::cout << std::endl << "Enter 'a' to enter food item" << std::endl;
		std::cout << "Enter 'b' to print today's log" << std::endl;
		std::cout << "Enter 'c' to save&close" << std::endl;

		std::cin >> userSelection;
		switch (userSelection)
		{
		case 'c':
			windowShouldClose = true;
			break;
		case 'a':
			log.addFood();
			break;
		case 'b':
			log.printTodaysLog();
			break;
		}

	
	}









}

