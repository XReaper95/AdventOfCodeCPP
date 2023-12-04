//
// Created by luisdt on 11/28/23.
//
#ifndef SOLUTION_H
#define SOLUTION_H

#include <chrono>
#include <fstream>
#include <filesystem>
#include <functional>

#include "fmt/printf.h"

class SolutionBase
{
public:
    void Run(const int example1Result, const int example2Result)
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

    virtual ~SolutionBase() = default;

protected:
    virtual int DayNum() = 0;
    virtual int Part1(std::fstream& inputFileStream) = 0;
    virtual int Part2(std::fstream& inputFileStream) = 0;

private:
    void SolveInput(
        const int partNum,
        int (SolutionBase::*PartFunc)(std::fstream&))
    {
        std::fstream inputStream = getFileStream(-1);

        const auto begin1 = std::chrono::high_resolution_clock::now();
        int result = (this->*PartFunc)(inputStream);
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

    void SolveExample(
        const int exampleNum,
        const int expectedResult,
        int (SolutionBase::*PartFunc)(std::fstream&))
    {
        std::fstream exampleStream = getFileStream(exampleNum);

        if (int result = (this->*PartFunc)(exampleStream); result > 0)
        {
            if (result == expectedResult)
            {
                fmt::println("Day {}, example {} result: {}. OK", DayNum(), exampleNum, result);
            }
            else
            {
                fmt::println(stderr, "ERROR day {} example {}, expected {}, received {}",
                             DayNum(), exampleNum, expectedResult, result);
                std::exit(1);
            }
        }
        else
        {
            fmt::println("Day {}, example {} not implemented", DayNum(), exampleNum);
        }
    }

    std::fstream getFileStream(const int exampleNum)
    {
        std::string dayStr = std::to_string(DayNum());

        // day 1-9 should be 0X
        if (DayNum() <= 9)
        {
            dayStr = "0" + dayStr;
        }

        std::string fileName;
        if (exampleNum > 0)
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
};

#endif //SOLUTION_H
