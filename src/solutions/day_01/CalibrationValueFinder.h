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
    explicit CalibrationValueFinder(const std::string& line, bool useNames);

    int GetResult();
private:
    bool m_useNames;
    std::stringstream m_stream;
    std::string m_compareBuffer;
    CalibrationResult m_result;

    bool ProcessPossibleDigit(char character);
    void SearchForName(char character);
};

#endif //DIGIT_FINDER_H
