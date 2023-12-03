//
// Created by luisdt on 12/2/23.
//
#include "CalibrationValueFinder.h"

#include <algorithm>
#include <string>
#include <unordered_map>

struct DigitMeta
{
    std::string restOfName;
    int digit;
};

static std::unordered_map<std::string, DigitMeta> digitsByName {
    {"on", {"e", 1}},
    {"tw", {"o", 2}},
    {"th", {"ree", 3}},
    {"fo", {"ur", 4}},
    {"fi", {"ve", 5}},
    {"si", {"x", 6}},
    {"se", {"ven", 7}},
    {"ei", {"ght", 8}},
    {"ni", {"ne", 9}}
};

void CalibrationResult::Update(const int digit)
{
    if (m_firstDigit == 0)
    {
        m_firstDigit = digit;
    } else
    {
        m_secondDigit = digit;
    }
}

void CalibrationResult::Update(const char digit)
{
    Update(digit - '0');
}

int CalibrationResult::Get()
{
    if (m_secondDigit == 0) m_secondDigit = m_firstDigit;
    return m_firstDigit * 10 + m_secondDigit;

}

CalibrationValueFinder::CalibrationValueFinder(const bool useNames)
    : m_useNames{useNames}
{
    m_compareBuffer.reserve(2);
    m_backupBuffer.reserve(3);
}


int CalibrationValueFinder::GetResultAndReset(std::stringstream& ss)
{
    char c;
    while(ss >> c)
    {
        if (!ProcessPossibleDigit(c) && m_useNames)
        {
            SearchForName(c, ss);
        }
    }

    const int result =  m_result.Get();

    //reset state
    m_compareBuffer.clear();
    m_backupBuffer.clear();
    m_result = CalibrationResult{};

    return result;
}

bool CalibrationValueFinder::ProcessPossibleDigit(const char character)
{
    if (std::isdigit(character))
    {
        m_result.Update(character);
        m_compareBuffer.clear();
        return true;
    }

    return false;
}

void CalibrationValueFinder::SearchForName(const char character, std::stringstream& ss)
{
    m_compareBuffer += character;
    if (m_compareBuffer.size() == 2)
    {
        if (digitsByName.contains(m_compareBuffer))
        {
            char fromStream;
            m_backupBuffer.clear();

            const auto [restOfName, digit] = digitsByName.at(m_compareBuffer);
            for (const auto c: restOfName)
            {
                ss >> fromStream;
                m_backupBuffer += fromStream;

                if (ProcessPossibleDigit(fromStream)) return;
                if (c != fromStream)
                {
                    m_compareBuffer.erase(0, 1);
                    std::ranges::for_each(
                        m_backupBuffer,
                        [&ss](const char backupChar){ss.putback(backupChar);}
                        );
                    return;
                }
            }
            m_result.Update(digit);
            ss.putback(fromStream);
        }

        m_compareBuffer.erase(0, 1);
    }
}
