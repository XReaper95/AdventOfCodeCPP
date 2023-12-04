#include <fstream>

#include "SolutionBase.h"
#include "CalibrationValueFinder.h"

class Day01 final : public SolutionBase
{
protected:
    int DayNum() override
    {
        return 1;
    }

    int Part1(std::fstream& inputFileStream) override
    {
        int sum{};

        std::string line;
        CalibrationValueFinder finder{false};

        while (std::getline(inputFileStream, line))
        {
            std::stringstream ss{line};
            sum += finder.GetResultAndReset(ss);
        }

        return sum;
    }

    int Part2(std::fstream& inputFileStream) override
    {
        int sum{};

        std::string line;
        CalibrationValueFinder finder{true};

        while (std::getline(inputFileStream, line))
        {
            std::stringstream ss{line};
            sum += finder.GetResultAndReset(ss);
        }

        return sum;
    }
};

int main()
{
    Day01().Run(142, 281);
}
