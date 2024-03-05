#include "SolutionBase.h"

class Day05 final : public SolutionBase
{
protected:
    int DayNum() override
    {
        return 5;
    };

    [[nodiscard]] int Part1(const std::vector<std::string>& inputLines) const override
    {

        return -1;
    }

    [[nodiscard]] int Part2(const std::vector<std::string>& inputLines) const override
    {
        return -1;
    }
};

int main()
{
    Day05().Run(35, -1);
}

