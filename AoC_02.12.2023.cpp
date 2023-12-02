#include <map>
#include <iostream>
#include <algorithm>
#include <string>
#include <fstream>
#include <sstream>

int main()
{
    size_t result = 0;
    std::string line;
    std::string token;
    std::string color;
    std::string amount;
    std::ifstream file("input.txt");

    if (file.is_open())
    {
        while (std::getline(file, line))
        {
            std::map<std::string, uint8_t> maxCubes { {"red", 0}, {"green", 0}, {"blue", 0} };
            line = line.substr(line.find(":") + 2);
            std::stringstream ss(line);
            while (std::getline(ss, token, ';'))
            {
                std::stringstream ss2(token);
                while (std::getline(ss2, token, ','))
                {
                    std::stringstream ss3(token);
                    ss3 >> amount;
                    ss3 >> color;
                    unsigned int value = std::stoi(amount);
                    if (maxCubes[color] < value)
                    {
                        maxCubes[color] = value;
                    }
                }
            }
            result += maxCubes["red"] * maxCubes["green"] * maxCubes["blue"];
        }

        file.close();
    }

    std::cout << result;
    return 0;
}
