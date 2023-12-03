//
// Created by luisdt on 11/28/23.
//
#ifndef SOLUTION_H
#define SOLUTION_H

#include <cassert>
#include <chrono>
#include <fstream>
#include <filesystem>

#include "fmt/printf.h"

class SolutionBase
{
public:
    void Solve(int dayNum)
    {
        // Part1
        const auto begin1 = std::chrono::high_resolution_clock::now();
        int result1 = Part1();
        const  auto end1 = std::chrono::high_resolution_clock::now();

        // Part1
        const auto begin2 = std::chrono::high_resolution_clock::now();
        int result2 = Part2();
        const auto end2 = std::chrono::high_resolution_clock::now();

        if (result1 > 0)
        {
            fmt::println("Day {}, part 1 result: {} completed in {} ms", dayNum, result1,
            std::chrono::duration<double, std::milli>(end1 - begin1).count());
        } else
        {
            fmt::println("Day {}, part 1 not implemented", dayNum);
        }

        if (result2 > 0)
        {
            fmt::println("Day {}, part 2 result: {} completed in {} ms", dayNum, result2,
            std::chrono::duration<double, std::milli>(end2 - begin2).count());
        } else
        {
            fmt::println("Day {}, part 2 not implemented", dayNum);
        }
    }

    virtual ~SolutionBase() = default;
protected:
    static std::fstream inputFileStream(const int dayNum)
    {
        std::string dayStr = std::to_string(dayNum);

        // day 1 should be 01
        if (dayNum == 1)
        {
            dayStr = "0" + dayStr;
        }

        const std::string inputPath {fmt::format("src/solutions/day_{}/input.txt", dayStr)};

        if (!std::filesystem::exists(inputPath))
        {
            fmt::println(stderr, "Cannot find '{}'", inputPath);
            assert(false);
        }

        return std::fstream { inputPath };
    }

    virtual int Part1() = 0;
    virtual int Part2() = 0;
};

#endif //SOLUTION_H
