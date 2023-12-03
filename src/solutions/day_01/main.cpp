#include <fstream>

#include "SolutionBase.h"
#include "CalibrationValueFinder.h"

class Day01 final: public SolutionBase
{
protected:
    int Part1() override
    {
        int sum {};

        std::string line;
        std::fstream file = inputFileStream(1);

        while (std::getline(file, line))
        {
            CalibrationValueFinder finder {line, false};
            sum += finder.GetResult();
        }

        return sum;
    }

    int Part2() override
    {
        int sum {};

        std::string line;
        std::fstream file = inputFileStream(1);

        while (std::getline(file, line))
        {
            CalibrationValueFinder finder {line, true};
            sum += finder.GetResult();
        }

        return sum;
    }
};


int main()
{
    Day01().Solve(1);
}

