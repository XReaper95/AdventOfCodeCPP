#include "SolutionBase.h"
#include "fmt/printf.h"


void SolutionBase::Run(const int example1Result, const int example2Result)
{
    if (DayNum() < 1 || DayNum() > 25)
    {
        fmt::println(stderr, "DayNum should be from 1 to 25 (got {})", DayNum());
        std::exit(1);
    }

    SolveExample(1, example1Result, &SolutionBase::Part1);
    SolveInput(1, &SolutionBase::Part1);
    fmt::println("------------------------------");
    SolveExample(2, example2Result, &SolutionBase::Part2);
    SolveInput(2, &SolutionBase::Part2);
}

void SolutionBase::SolveInput(const int partNum, const SolutionPartFunction partFunc)
{
    std::fstream inputStream = getFileStream(-1);

    const auto begin1 = std::chrono::high_resolution_clock::now();
    int result = (this->*partFunc)(inputStream);
    const auto end1 = std::chrono::high_resolution_clock::now();

    if (result > 0)
    {
        fmt::println("Day {}, part {} result: {} completed in {} ms", DayNum(), partNum, result,
                     std::chrono::duration<double, std::milli>(end1 - begin1).count());
    }
    else
    {
        fmt::println("Day {}, part {} not implemented", DayNum(), partNum);
    }
}

void SolutionBase::SolveExample(const int exampleNum, const int expectedResult, const SolutionPartFunction partFunc)
{
    std::fstream exampleStream = getFileStream(exampleNum);

    if (int result = (this->*partFunc)(exampleStream); result >= 0)
    {
        if (result == expectedResult)
        {
            fmt::println("Day {}, example {} result: {} (OK)", DayNum(), exampleNum, result);
        }
        else
        {
            fmt::println(stderr, "ERROR day {} example {}, expected: {} received: {}",
                         DayNum(), exampleNum, expectedResult, result);
            std::exit(1);
        }
    }
    else
    {
        fmt::println("Day {}, example {} not implemented", DayNum(), exampleNum);
    }
}

std::fstream SolutionBase::getFileStream(const int exampleNum)
{
    std::string dayStr = std::to_string(DayNum());

    // day 1-9 should be 0X
    if (DayNum() <= 9)
    {
        dayStr = "0" + dayStr;
    }

    std::string fileName;
    if (exampleNum >= 0)
    {
        fileName = fmt::format("example_{}.txt", exampleNum);
    }
    else
    {
        fileName = "input.txt";
    }

    std::string inputPath = fmt::format("inputs/day_{}/{}", dayStr, fileName);

    if (!std::filesystem::exists(inputPath))
    {
        fmt::println(stderr, "Cannot find '{}'", inputPath);
        std::exit(1);
    }

    return std::fstream{inputPath};
}
