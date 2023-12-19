//
// Created by luisdt on 11/28/23.
//
#ifndef SOLUTION_H
#define SOLUTION_H

#include <filesystem>
#include <vector>

class SolutionBase
{
public:
    void Run(int example1Result, int example2Result);

    virtual ~SolutionBase() = default;

protected:
    virtual int DayNum() = 0;
    [[nodiscard]] virtual int Part1(const std::vector<std::string>& inputLines) const = 0;
    [[nodiscard]] virtual int Part2(const std::vector<std::string>& inputLines) const = 0;

private:
    using SolutionPartFunction = int(SolutionBase::*)(const std::vector<std::string>&) const;

    void SolveInput(int partNum, SolutionPartFunction partFunc);
    void SolveExample(int exampleNum, int expectedResult, SolutionPartFunction partFunc);
    std::vector<std::string> readFileLines(int exampleNum);
};

#endif //SOLUTION_H
