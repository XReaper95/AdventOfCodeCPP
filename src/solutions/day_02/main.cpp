#include <fstream>

#include "SolutionBase.h"

class Day02 final : public SolutionBase
{
protected:
    int DayNum() override
    {
        return 1;
    };

    int Part1(std::fstream& inputFileStream) override
    {
        return -1;
    }

    int Part2(std::fstream& inputFileStream) override
    {
        return -1;
    }
};

int main()
{
    Day02().Run(142, 281);
}

