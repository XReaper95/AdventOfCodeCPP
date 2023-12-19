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

    [[nodiscard]] int Part1(const std::vector<std::string>& inputLines) const override
    {
        std::unordered_map<std::string, int> colorLimits{
            {"red", 12}, {"green", 13}, {"blue", 14}
        };

        int validGamesSum{};
        std::string tempBuf;
        int currGame{};

        for (auto& line : inputLines)
        {
            bool validGame {true};
            std::stringstream ss {line};
            ss >> tempBuf; // "Game" word
            ss >> currGame;

            while (ss >> tempBuf)
            {
                if (std::isdigit(tempBuf[0]))
                {
                    const int colorCount = std::stoi(tempBuf);
                    ss >> tempBuf; // get color

                    if (endsInPunctuacion(tempBuf))
                    {
                        tempBuf.pop_back();
                    }

                    if (colorCount > colorLimits[tempBuf])
                    {
                        validGame = false;
                        break;
                    }
                }
            }

            if (validGame) validGamesSum += currGame;
        }

        return validGamesSum;
    }

    [[nodiscard]] int Part2(const std::vector<std::string>& inputLines) const override
    {
        int r{}, g{}, b{};
        std::string tempBuf;
        int powerSum{};
        int currGame{};

        for (auto& line : inputLines)
        {
            std::stringstream ss {line};
            ss >> tempBuf; // "Game" word
            ss >> currGame;

            while (ss >> tempBuf)
            {
                if (std::isdigit(tempBuf[0]))
                {
                    const int colorCount = std::stoi(tempBuf);
                    ss >> tempBuf;

                    if (endsInPunctuacion(tempBuf))
                    {
                        tempBuf.pop_back();
                    }

                    if (tempBuf == "red"   && colorCount > r) r = colorCount;
                    if (tempBuf == "green" && colorCount > g) g = colorCount;
                    if (tempBuf == "blue"  && colorCount > b) b = colorCount;
                }
            }

            powerSum += r * g * b;
            r = g = b = 0;
        }

        return powerSum;
    }

    static bool endsInPunctuacion(const std::string_view text)
    {
        return text[text.size() - 1] == ',' || text[text.size() - 1] == ';';
    }
};

int main()
{
    Day02().Run(8, 2286);
}
