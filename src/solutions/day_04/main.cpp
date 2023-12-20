#include <charconv>
#include <cmath>
#include <numeric>
#include <ranges>
#include <set>

#include "SolutionBase.h"
#include "Utils.h"

#include "boost/algorithm/string.hpp"

class Day04 final : public SolutionBase
{
protected:
    int DayNum() override
    {
        return 4;
    };

    [[nodiscard]] int Part1(const std::vector<std::string>& inputLines) const override
    {
        int sum{};
        for (const std::string_view line : inputLines)
        {
            if (line.empty()) continue;

            Card card {line};

            if (const size_t matching = card.matchingNumbers(); matching > 0)
            {
                sum += static_cast<int>(std::pow(2, matching - 1));
            }
        }

        return sum;
    }

    [[nodiscard]] int Part2(const std::vector<std::string>& inputLines) const override
    {
        std::vector cardCount (inputLines.size(), 1);

        for (const std::string_view line : inputLines)
        {
            if (line.empty()) continue;

            Card card {line};
            const size_t matching = card.matchingNumbers();

            for (int i = 1; i <= matching; i++)
            {
                cardCount[card.getId() - 1 + i] += cardCount[card.getId() - 1];
            }
        }

        return std::accumulate(cardCount.begin(), cardCount.end(), 0);
    }
private:
    class Card
    {
    public:
        explicit Card(const std::string_view line)
        {
            const auto parts = SplitString(line, [](auto c) { return c == ':' || c == '|';});

            const auto idPart = SplitString(parts[0], ' ');
            const auto idStrv = idPart[idPart.size() - 1];
            std::from_chars(idStrv.data(), idStrv.data() + idStrv.size(), m_id);

            m_winners = SplitString<std::set>(parts[1], ' ');
            m_numbers = SplitString<std::set>(parts[2], ' ');

            // correction for the parsing always having a leading space
            m_winners.erase(m_winners.begin());
            m_numbers.erase(m_numbers.begin());
        }

        [[nodiscard]] int getId() const { return m_id;}

        [[nodiscard]] size_t matchingNumbers() const
        {
            std::vector<std::string_view> result;
            std::ranges::set_intersection(m_winners, m_numbers, std::back_inserter(result));
            return result.size();
        }

    private:
        int m_id{};
        std::set<std::string_view> m_winners;
        std::set<std::string_view> m_numbers;
    };
};

int main()
{
    Day04().Run(13, 30);
}

