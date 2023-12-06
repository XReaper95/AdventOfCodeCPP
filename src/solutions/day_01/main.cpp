#include "SolutionBase.h"
#include "CalibrationValueFinder.h"

class Day01 final : public SolutionBase
{
protected:
    int DayNum() override
    {
        return 1;
    }

    int Part1(std::ifstream& inputFile) override
    {
        CalibrationValueFinder finder;
        return finder.CalculateResult(inputFile, false);
    }

    int Part2(std::ifstream& inputFile) override
    {
        CalibrationValueFinder finder;
        return finder.CalculateResult(inputFile, true);
    }
};

int main()
{
    Day01().Run(142, 281);
}
