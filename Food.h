#pragma once

class Food
{
private:
	std::string name;
	float calories;
	float protein;

public:
	Food(std::string name, float cal, float protein)
	{
		this->name = name;
		this->calories = cal;
		this->protein = protein;
	}

	const std::string getName() const
	{
		return this->name;
	}

	const float getCalories() const
	{
		return this->calories;
	}

	const float getProtein() const
	{
		return this->protein;
	}
};