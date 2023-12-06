//
// Created by luisdt on 12/2/23.
//
#include "CalibrationValueFinder.h"

#include <string>
#include <unordered_map>

static constexpr int numDigits = 9;
static const char* digitNames[numDigits] = {
    "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"
};

int CalibrationValueFinder::CalculateResult(std::ifstream& ifs, const bool useNames)
{
    std::string lineBuffer;
    while (std::getline(ifs, lineBuffer))
    {
        std::string_view line {lineBuffer};
        for (int i{}; i < line.size(); i++)
        {
            if (const char c {line[i]}; std::isdigit(c))
            {
                StoreDigit(c);
                continue;
            }

            if (useNames)
            {
                for (int n{}; n < numDigits; n++)
                {
                    if (line.substr(i).starts_with(digitNames[n]))
                    {
                        StoreDigit(n + 1);
                    }
                }
            }
        }

        StoreLineResult();
    }

    return m_accumulator;
}

void CalibrationValueFinder::StoreDigit(const char digit)
{
    StoreDigit(digit - '0');
}

void CalibrationValueFinder::StoreDigit(const int digit)
{
    m_firstDigit == 0 ? m_firstDigit = digit : m_secondDigit = digit;
}

void CalibrationValueFinder::StoreLineResult()
{
    if (m_secondDigit == 0) m_secondDigit = m_firstDigit;
    m_accumulator += m_firstDigit * 10 + m_secondDigit;

    m_firstDigit = 0;
    m_secondDigit = 0;
}
