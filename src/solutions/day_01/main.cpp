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
        CalibrationValueFinder finder {false};

        while (std::getline(file, line))
        {
            std::stringstream ss {line};
            sum += finder.GetResultAndReset(ss);
        }

        return sum;
    }

    int Part2() override
    {
        int sum {};

        std::string line;
        std::fstream file = inputFileStream(1);
        CalibrationValueFinder finder {true};

        while (std::getline(file, line))
        {
            std::stringstream ss {line};
            sum += finder.GetResultAndReset(ss);
        }

        return sum;
    }
};


int main()
{
    Day01().Solve(1);
}

