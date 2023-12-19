#include "SolutionBase.h"
#include "CalibrationValueFinder.h"

class Day01 final : public SolutionBase
{
protected:
    int DayNum() override
    {
        return 1;
    }

    [[nodiscard]] int Part1(const std::vector<std::string>& inputLines) const override
    {
        CalibrationValueFinder finder;
        return finder.CalculateResult(inputLines, false);
    }

    [[nodiscard]] int Part2(const std::vector<std::string>& inputLines) const override
    {
        CalibrationValueFinder finder;
        return finder.CalculateResult(inputLines, true);
    }
};

int main()
{
    Day01().Run(142, 281);
}
