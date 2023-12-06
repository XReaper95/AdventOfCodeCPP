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

    int Part1(std::ifstream& inputFile) override
    {
        std::unordered_map<std::string, int> colorLimits{
            {"red", 12}, {"green", 13}, {"blue", 14}
        };

        int validGamesSum{};
        std::string tempBuf;
        int currGame{};

        while (inputFile >> tempBuf)
        {
            if (tempBuf == "Game")
            {
                if (currGame > 0)
                {
                    validGamesSum += currGame;
                }
                inputFile >> currGame;
            }

            if (std::isdigit(tempBuf[0]))
            {
                const int colorCount = std::stoi(tempBuf);
                inputFile >> tempBuf;

                if (endsInPunctuacion(tempBuf))
                {
                    tempBuf.pop_back();
                }

                if (colorCount > colorLimits[tempBuf])
                {
                    currGame = -1;
                    skipToNextLine(inputFile);
                }
            }
        }

        if (currGame > 0) validGamesSum += currGame;

        return validGamesSum;
    }

    int Part2(std::ifstream& inputFile) override
    {
        std::string tempBuf;
        std::unordered_map<std::string, int> minimumSet;
        int powerSum{};

        while (inputFile >> tempBuf)
        {
            if (tempBuf == "Game")
            {
                if (!minimumSet.empty()) powerSum += extractMinimunSetPower(minimumSet);
                skipToSemicolon(inputFile);
                continue;
            }

            if (std::isdigit(tempBuf[0]))
            {
                const int colorCount = std::stoi(tempBuf);
                inputFile >> tempBuf;

                if (endsInPunctuacion(tempBuf))
                {
                    tempBuf.pop_back();
                }

                minimumSet.insert({tempBuf, colorCount});
                if (colorCount > minimumSet[tempBuf])
                {
                    minimumSet[tempBuf] = colorCount;
                }
            }
        }

        powerSum += extractMinimunSetPower(minimumSet);

        return powerSum;
    }

    static bool endsInPunctuacion(const std::string_view text)
    {
        return text[text.size() - 1] == ',' || text[text.size() - 1] == ';';
    }

    static void skipToNextLine(std::ifstream& ifs)
    {
        ifs.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    static void skipToSemicolon(std::ifstream& ifs)
    {
        ifs.ignore(std::numeric_limits<std::streamsize>::max(), ':');
    }

    static int extractMinimunSetPower(std::unordered_map<std::string, int>& minimumSet)
    {
        const int result = std::accumulate(
            minimumSet.begin(),
            minimumSet.end(),
            1,
            [](const int previous, const auto& p) { return previous * p.second; }
        );

        minimumSet.clear();

        return result;
    }
};

int main()
{
    Day02().Run(8, 2286);
}
