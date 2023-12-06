//
// Created by luisdt on 12/2/23.
//
#include "CalibrationValueFinder.h"

#include <string>
#include <unordered_map>

struct DigitMeta
{
    std::string restOfName;
    int digit{};
};

constexpr int numDigits = 9;

static const char* namedDigits[numDigits] = {
    "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"
};

void CalibrationResult::Update(const int digit)
{
    if (m_firstDigit == 0)
    {
        m_firstDigit = digit;
    }
    else
    {
        m_secondDigit = digit;
    }
}

void CalibrationResult::Update(const char digit)
{
    Update(digit - '0');
}

void CalibrationResult::StoreLineResult()
{
    if (m_secondDigit == 0) m_secondDigit = m_firstDigit;
    m_accumulator += m_firstDigit * 10 + m_secondDigit;

    m_firstDigit = 0;
    m_secondDigit = 0;
}

int CalibrationValueFinder::CalculateResult(std::ifstream& ifs, const bool useNames)
{
    while (std::getline(ifs, m_lineBuffer))
    {
        for (int i{}; i < m_lineBuffer.size(); i++)
        {
            if (!ProcessPossibleDigit(m_lineBuffer[i]) && useNames)
            {
                for (int n{}; n < numDigits; n++)
                {
                    if (m_lineBuffer.substr(i).starts_with(namedDigits[n]))
                    {
                        m_result.Update(n + 1);
                    }
                }
            }
        }

        m_result.StoreLineResult();
    }

    return m_result.Get();
}

bool CalibrationValueFinder::ProcessPossibleDigit(const char character)
{
    if (std::isdigit(character))
    {
        m_result.Update(character);
        return true;
    }

    return false;
}


void CalibrationValueFinder::ProcessNextLine()
{
    m_lineBuffer.clear();
    m_result.StoreLineResult();
}
