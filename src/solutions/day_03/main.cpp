#include "SolutionBase.h"

class Day03 final : public SolutionBase
{
protected:
    int DayNum() override
    {
        return 3;
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
    Day03().Run(-1, -1);
}

