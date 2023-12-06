//
// Created by luisdt on 11/28/23.
//
#ifndef SOLUTION_H
#define SOLUTION_H

#include <fstream>
#include <filesystem>

class SolutionBase
{
public:
    void Run(int example1Result, int example2Result);

    virtual ~SolutionBase() = default;

protected:
    virtual int DayNum() = 0;
    virtual int Part1(std::ifstream& inputFile) = 0;
    virtual int Part2(std::ifstream& inputFile) = 0;

private:
    using SolutionPartFunction = int(SolutionBase::*)(std::ifstream&);

    void SolveInput(int partNum, SolutionPartFunction partFunc);
    void SolveExample(int exampleNum, int expectedResult, SolutionPartFunction partFunc);
    std::ifstream getFileStream(int exampleNum);
};

#endif //SOLUTION_H
