#include "FoodLog.h"
#include <chrono>
#include <ctime>
#include <sstream>
#include <fstream>
#include <string>
#include <filesystem>

namespace fs = std::filesystem;

FoodLog::FoodLog()
{
    std::ifstream checkOpen;
    fs::path path = fs::current_path();
    std::string pathString = path.string();
    pathString += "\\food.log";
    std::cout << pathString << std::endl;

    this->filePath = pathString;

    checkOpen.open(pathString);
    if (!checkOpen.is_open())
    {
        std::cout << "No file found - creating file" << std::endl;
        std::ofstream createFile(pathString);
        createFile << this->getTodaysDate() << ' ';
        createFile.close();

    }
    else
    {
        std::cout << "File found" << std::endl;
    }

    checkOpen.close();
	
}

unsigned int FoodLog::getTodaysDate()
{
    unsigned int dateAsInteger;
    auto now = std::chrono::system_clock::now();

    // Convert the time point to a time_t (timestamp)
    std::time_t time = std::chrono::system_clock::to_time_t(now);

    // Create a struct tm to hold the date and time components
    std::tm tm_info = {};

    // Use localtime_s to safely convert the timestamp to a struct tm
    if (localtime_s(&tm_info, &time) == 0)
    {
        // Calculate the date as an integer in YYYYMMDD format
        dateAsInteger = (tm_info.tm_year + 1900) * 10000 + (tm_info.tm_mon + 1) * 100 + tm_info.tm_mday;
    }
    else
    {
        std::cout << "Error: Date conversion failed.\n";
        exit(-1);
    }
	return dateAsInteger;
}

void FoodLog::readLog()
{
    if (log.size() != 0)
    {
        log.clear();
    }
    
    //read all contents, and put map date with a vector of Food objects.
    //if the last key is the same as getTodaysDate(), dont create a new line
    std::string line, key, line2, name, kcal, protein;
    std::ifstream inFile("food.log");
    if (!inFile.fail())
    {
        while (std::getline(inFile, line))
        {
            std::stringstream sstream(line);
            int step = 0;

            while (sstream >> line2)
            {
                switch (step)
                {
                case 0:
                    key = line2;
                    step++;
                    break;
                case 1:
                    name = line2;
                    step++;
                    break;
                case 2:
                    kcal = line2;
                    step++;
                    break;
                case 3:
                    protein = line2;
                    step = 1;
                    log[stoi(key)].push_back(Food(name, (float)stoi(kcal), (float)stoi(protein)));
                    break;
                }
            }


        }
        inFile.close();

        //std::string key now holds the last recorded date
        if ((unsigned int)stoi(key) != this->getTodaysDate())
        {
            std::ofstream out(this->filePath, std::ios_base::app);
            out << std::endl << this->getTodaysDate() << ' ';
            out.close();
        }


    }
    else
    {
        std::cout << "FoodLog.cpp - inFile failed to open\n";
        exit(-1);
    }

}

void FoodLog::addFood()
{
    std::string temp_name;
    float temp_cal, temp_protein;
    float quantity;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Enter name of food: ";
    std::getline(std::cin, temp_name);

    for (auto& ch : temp_name)
    {
        if (ch == ' ')
        {
            ch = '_';
        }
    }
    std::cout << "Enter calorie amount: ";
    std::cin >> temp_cal;
    std::cout << "Enter grams of protein: ";
    std::cin >> temp_protein;
    std::cout << "Enter number of servings: ";
    std::cin >> quantity;
    this->log[this->getTodaysDate()].push_back(Food(temp_name, temp_cal * quantity, temp_protein * quantity));
    
    std::ofstream outFile(filePath, std::ios_base::app);
    outFile << temp_name << ' ' << temp_cal * quantity << ' ' << temp_protein * quantity << ' ';

    outFile.close();
}

float FoodLog::getCalsProtein(const float& CAL_GOAL)
{
    float eaten_calories{ 0 };
    float protein{ 0 };

    auto it = this->log[this->getTodaysDate()].begin();
    auto end_it = this->log[this->getTodaysDate()].end();
    while (it != end_it)
    {
        eaten_calories += it->getCalories();
        protein += it->getProtein();
        it++;
    }

    eaten_calories = CAL_GOAL - eaten_calories;

    std::cout << "Calories remaining: " << eaten_calories << std::endl;
    std::cout << protein << "g protein eaten." << std::endl;


}

void FoodLog::printTodaysLog()
{
    std::cout << "Today's log: " << std::endl;
    auto it = this->log[this->getTodaysDate()].begin();
    auto end_it = this->log[this->getTodaysDate()].end();
    while (it != end_it)
    {
        std::cout << it->getName() << ": " << it->getCalories() << "kcal " << it->getProtein() << "g protein" << std::endl;
        it++;
    }
    std::cout << std::endl;
}