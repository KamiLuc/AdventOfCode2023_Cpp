#include <vector>
#include <list>
#include <iostream>
#include <algorithm>
#include <string>
#include <fstream>
#include <sstream>

struct Number
{
	std::string value;
	int xBeginPos;
	int xEndPos;
	int yPos;

	void parseNumber(const std::string& line, int xBegin, int y)
	{
		xBeginPos = xBegin;
		yPos = y;

		for (; xBegin < line.size(); ++xBegin)
		{
			if (!std::isdigit(line[xBegin]))
			{
				break;
			}
			value += line[xBegin];
		}

		xEndPos = xBeginPos + value.size() - 1;
	}
};

int main()
{
	size_t result = 0;
	int yIndex = 0;
	std::string line;
	std::ifstream file("input.txt");
	std::list<Number> numbers;
	std::list<std::pair<int, int>> gears;

	if (file.is_open())
	{
		while (std::getline(file, line))
		{
			for (int xIndex = 0; xIndex < line.size(); ++xIndex)
			{
				if (std::isdigit(line[xIndex]))
				{
					Number number;
					number.parseNumber(line, xIndex, yIndex);
					numbers.emplace_back(number);
					xIndex += number.value.size() - 1;
				}
				else if (line[xIndex] == '*')
				{
					gears.emplace_back(std::make_pair(xIndex, yIndex));
				}
			}

			++yIndex;
		}

		file.close();
	}

	for (const auto& gear : gears)
	{
		std::list<Number> validNumbers;
		for (const auto& number : numbers)
		{
			if (number.yPos <= gear.second + 1 &&
				number.yPos >= gear.second - 1)
			{
				if (number.xBeginPos - 1 <= gear.first &&
					number.xEndPos + 1 >= gear.first)
				{
					validNumbers.emplace_back(number);
				}
			}
		}

		if (validNumbers.size() == 2)
		{
			result += std::stoi(validNumbers.front().value) * std::stoi(validNumbers.back().value);
		}
	}

	std::cout << result;
	return 0;
}
