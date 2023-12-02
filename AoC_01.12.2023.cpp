#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

int main()
{
    size_t result = 0;
    std::string line;
    std::ifstream file("input.txt");
    std::vector<std::string> digitStrings {
        "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    if (file.is_open())
    {
        while (std::getline(file, line))
        {
            std::vector<std::string> digits;

            for (size_t i = 0; i < line.size(); ++i)
            {
                if (std::isdigit(line[i]))
                {
                    line.replace(i, 1, digitStrings[line[i] - '0']);
                }
            }

            for (size_t i = 0; i < line.size(); ++i)
            {
                for (size_t j = 0; j < digitStrings.size(); ++j)
                {
                    if (line.substr(i, digitStrings[j].size()) == digitStrings[j])
                    {
                        digits.push_back(std::to_string(j));
			break;
                    }
                }
            }
            
            result += std::stoi(digits.front() + digits.back());
        }

        file.close();
    }

    std::cout << result;
    return 0;
}
