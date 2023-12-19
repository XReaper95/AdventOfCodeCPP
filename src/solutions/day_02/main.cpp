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

        while (inputLines >> tempBuf)
        {
            if (tempBuf == "Game")
            {
                if (currGame > 0)
                {
                    validGamesSum += currGame;
                }
                inputLines >> currGame;
            }

            if (std::isdigit(tempBuf[0]))
            {
                const int colorCount = std::stoi(tempBuf);
                inputLines >> tempBuf;

                if (endsInPunctuacion(tempBuf))
                {
                    tempBuf.pop_back();
                }

                if (colorCount > colorLimits[tempBuf])
                {
                    currGame = -1;
                    skipToNextLine(inputLines);
                }
            }
        }

        if (currGame > 0) validGamesSum += currGame;

        return validGamesSum;
    }

    [[nodiscard]] int Part2(const std::vector<std::string>& inputLines) const override
    {
        std::string tempBuf;
        int r{}, g{}, b{};
        int powerSum{};

        while (inputLines >> tempBuf)
        {
            if (tempBuf == "Game")
            {
                inputLines >> tempBuf; // skip game number
                inputLines >> tempBuf; // get first color number

                powerSum += r * g * b;
                r = g = b = 0;
            }

            if (std::isdigit(tempBuf[0]))
            {
                const int colorCount = std::stoi(tempBuf);
                inputLines >> tempBuf;

                if (endsInPunctuacion(tempBuf))
                {
                    tempBuf.pop_back();
                }

                if (tempBuf == "red"   && colorCount > r) r = colorCount;
                if (tempBuf == "green" && colorCount > g) g = colorCount;
                if (tempBuf == "blue"  && colorCount > b) b = colorCount;
            }
        }

        return powerSum + r * g * b;
    }

    static bool endsInPunctuacion(const std::string_view text)
    {
        return text[text.size() - 1] == ',' || text[text.size() - 1] == ';';
    }

    static void skipToNextLine(std::ifstream& ifs)
    {
        ifs.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
};

int main()
{
    Day02().Run(8, 2286);
}
