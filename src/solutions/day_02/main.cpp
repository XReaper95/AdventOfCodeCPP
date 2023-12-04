#include <functional>
#include <numeric>
#include <unordered_map>
#include <fmt/core.h>

#include "SolutionBase.h"

class Day02 final : public SolutionBase
{
protected:
    int DayNum() override
    {
        return 2;
    };

    int Part1(std::fstream& inputFileStream) override
    {
        std::unordered_map<std::string, int> colorLimits {
            {"red", 12}, {"green", 13}, {"blue", 14}
        };

        std::string line;
        int validGamesSum {};
        std::string tempBuf;
        int currGame{};

        while (std::getline(inputFileStream, line))
        {
            std::stringstream ss{line};
            bool isGameValid = true;

            ss >> tempBuf; // game word
            ss >> currGame;

            while (ss >> tempBuf)
            {
                if (std::isdigit(tempBuf[0]))
                {
                    const int colorCount = std::stoi(tempBuf);
                    ss >> tempBuf;
                    std::string color;
                    std::ranges::remove_copy_if( // clear punctuation
                        tempBuf,
                        std::back_inserter(color),
                        [](const int c) { return std::ispunct(c);}
                    );

                    if (colorCount > colorLimits[color]) {
                        isGameValid = false;
                        break;
                    }
                }
            }

            if (isGameValid) validGamesSum += currGame;
        }

        return validGamesSum;
    }

    int Part2(std::fstream& inputFileStream) override
    {
        std::string line;
        int powerSum {};
        std::string tempBuf;

        while (std::getline(inputFileStream, line))
        {
            std::stringstream ss{line};

            std::unordered_map<std::string, int> minimumSet;
            minimumSet.reserve(3);

            ss >> tempBuf; // game word
            ss >> tempBuf; // current game, not needed here

            while (ss >> tempBuf)
            {
                if (std::isdigit(tempBuf[0]))
                {
                    const int colorCount = std::stoi(tempBuf);
                    ss >> tempBuf;
                    std::string color;
                    std::ranges::remove_copy_if( // clear punctuation
                        tempBuf,
                        std::back_inserter(color),
                        [](const int c) { return std::ispunct(c);}
                    );

                    minimumSet.insert({color, colorCount});
                    if (colorCount > minimumSet[color])
                    {
                        minimumSet[color] = colorCount;
                    }
                }
            }
            powerSum += std::accumulate(
                minimumSet.begin(),
                minimumSet.end(),
                1,
                [](const int previous, const auto& p) { return previous * p.second; }
                );
        }

        return powerSum;
    }
};

int main()
{
    Day02().Run(8, 2286);
}

