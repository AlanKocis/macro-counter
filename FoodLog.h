#pragma once
#include <iostream>
#include <map>
#include <vector>
#include <chrono>
#include "Food.h"

class FoodLog
{
private:
	std::map<unsigned int, std::vector<Food>> log;
	std::string filePath;
public:
	FoodLog();
	unsigned int getTodaysDate();
	void readLog();
	void addFood();
	float getCalsProtein(const float& CAL_GOAL);
	void printTodaysLog();
};