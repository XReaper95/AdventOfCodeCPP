//
// Created by luisdt on 12/2/23.
//

#ifndef DIGIT_FINDER_H
#define DIGIT_FINDER_H

#include <fstream>
#include <string>

class CalibrationResult
{
public:
    void Update(int digit);
    void Update(char digit);
    void StoreLineResult();
    [[nodiscard]] int Get() const { return m_accumulator; }

private:
    int m_firstDigit{};
    int m_secondDigit{};
    int m_accumulator{};
};

class CalibrationValueFinder
{
public:
    int CalculateResult(std::ifstream& ifs, bool useNames);

private:
    std::string m_lineBuffer;
    CalibrationResult m_result;

    bool ProcessPossibleDigit(char character);
    void ProcessNextLine();
};

#endif //DIGIT_FINDER_H
