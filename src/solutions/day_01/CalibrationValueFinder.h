//
// Created by luisdt on 12/2/23.
//

#ifndef DIGIT_FINDER_H
#define DIGIT_FINDER_H

#include <fstream>
#include <vector>

class CalibrationValueFinder
{
public:
    int CalculateResult(const std::vector<std::string>& lines, bool useNames);

private:
    int m_firstDigit{};
    int m_secondDigit{};
    int m_accumulator{};

    void StoreDigit(char digit);
    void StoreDigit(int digit);
    void StoreLineResult();
};

#endif //DIGIT_FINDER_H
