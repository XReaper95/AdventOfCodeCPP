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

CalibrationValueFinder::CalibrationValueFinder(const std::string& line, const bool useNames)
    : m_useNames{useNames}, m_stream{line}
{
}


int CalibrationValueFinder::GetResult()
{
    char c;
    while(m_stream >> c)
    {
        if (!ProcessPossibleDigit(c) && m_useNames)
        {
            SearchForName(c);
        }
    }

    return m_result.Get();
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

void CalibrationValueFinder::SearchForName(const char character)
{
    m_compareBuffer += character;
    if (m_compareBuffer.size() == 2)
    {
        if (digitsByName.contains(m_compareBuffer))
        {
            char fromStream;
            std::string backupBuffer;

            const auto [restOfName, digit] = digitsByName.at(m_compareBuffer);
            for (const auto c: restOfName)
            {
                m_stream >> fromStream;
                backupBuffer += fromStream;

                if (ProcessPossibleDigit(fromStream)) return;
                if (c != fromStream)
                {
                    m_compareBuffer.erase(0, 1);
                    for (const auto backupChar: backupBuffer)
                    {
                        m_stream.putback(backupChar);
                    }
                    return;
                }
            }
            m_result.Update(digit);
            m_stream.putback(fromStream);
        }

        m_compareBuffer.erase(0, 1);
    }
}
