#include <vector>
#include <list>
#include <iostream>
#include <algorithm>
#include <string>
#include <fstream>
#include <sstream>
#include <map>

struct Card
{
	int copies = 1;
	std::vector<int> winningNumbers;
	std::vector<int> numbers;
};

int main()
{
	size_t result = 0;
	std::string line;
	std::string half;
	std::string number;
	std::ifstream file("input.txt");
	int cardIndex = 1;
	std::map<int, Card> cards;

	if (file.is_open())
	{
		while (std::getline(file, line))
		{
			bool firstHalf = true;
			line = line.substr(line.find_first_of(':') + 1);
			std::stringstream ss1(line);
			Card card;

			while (std::getline(ss1, half, '|'))
			{
				std::stringstream ss2(half);

				while (ss2 >> number)
				{
					if (firstHalf)
					{
						card.winningNumbers.emplace_back(std::stoi(number));
					}
					else
					{
						card.numbers.emplace_back(std::stoi(number));
					}
				}

				firstHalf = false;
			}

			cards[cardIndex] = card;
			++cardIndex;
		}

		file.close();
	}

	for (auto& card : cards)
	{
		int wonCopies = 0;
		int cardIndex = card.first;
		for (const auto& winningNumber : card.second.winningNumbers)
		{
			auto& n = card.second.numbers;
			if (std::find(n.begin(), n.end(), winningNumber) != n.end())
			{
				++wonCopies;
			}
		}

		for (int i = 0; i < wonCopies; ++i)
		{
			if (cardIndex + i < cards.size())
			{
				cards[cardIndex + 1 + i].copies += card.second.copies;
			}
			else
			{
				break;
			}
		}

		result += card.second.copies;
	}

	std::cout << result;
	return 0;
}
