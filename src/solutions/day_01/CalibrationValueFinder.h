//
// Created by luisdt on 12/2/23.
//

#ifndef DIGIT_FINDER_H
#define DIGIT_FINDER_H

#include <sstream>
#include <string>

class CalibrationResult
{
public:
    void Update(int digit);
    void Update(char digit);
    [[nodiscard]] int Get();
private:
    int m_firstDigit {};
    int m_secondDigit {};
};

class CalibrationValueFinder
{
public:
    explicit CalibrationValueFinder(bool useNames);

    int GetResultAndReset(std::stringstream& ss);
private:
    bool m_useNames;
    std::string m_compareBuffer;
    std::string m_backupBuffer;
    CalibrationResult m_result;

    bool ProcessPossibleDigit(char character);
    void SearchForName(char character, std::stringstream& ss);
};

#endif //DIGIT_FINDER_H
