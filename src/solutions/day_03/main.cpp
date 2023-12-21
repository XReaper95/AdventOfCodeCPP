#include <algorithm>
#include <charconv>
#include <numeric>
#include <optional>
#include <ranges>
#include <unordered_map>

#include "SolutionBase.h"

class Day03 final : public SolutionBase
{
protected:
    int DayNum() override
    {
        return 3;
    }

    [[nodiscard]] int Part1(const std::vector<std::string>& inputLines) const override
    {
        int sum {};

        for (int lineIndex {}; lineIndex < inputLines.size(); lineIndex++)
        {
            std::string_view line {inputLines[lineIndex]};
            for (int charIndex {}; charIndex < line.size(); charIndex++)
            {
                if (std::isdigit(line[charIndex]))
                {
                    if (NextTo(
                        charIndex,
                        GetLine(lineIndex - 1, inputLines),
                        GetLine(lineIndex, inputLines),
                        GetLine(lineIndex + 1, inputLines)))
                    {
                        {
                            auto [value, nextIndex] = ExtractNumberAndLastPosition(charIndex, line);
                            charIndex = nextIndex;
                            sum += value;
                        }
                    }
                }

            }
        }

        return sum;
    }

    [[nodiscard]] int Part2(const std::vector<std::string>& inputLines) const override
    {
        // only works if all lines are same size, which they are
        const size_t lineLenght = inputLines.size();
        // maps gear position to its two part numbers
        std::unordered_map<int, Gear> gears;

        for (int lineIndex {}; lineIndex < inputLines.size(); lineIndex++)
        {
            std::string_view line {inputLines[lineIndex]};
            for (int charIndex {}; charIndex < line.size(); charIndex++)
            {
                if (std::isdigit(line[charIndex]))
                {
                    if (const int gearPosition = AdjacentGearPosition(charIndex, lineIndex, lineLenght, inputLines);
                        gearPosition >= 0)
                    {
                        auto [value, nextIndex] = ExtractNumberAndLastPosition(charIndex, line);
                        charIndex = nextIndex;

                        if (gears.contains(gearPosition))
                        {
                            gears.at(gearPosition).AddPart2(value);
                        }
                        else
                        {
                            gears[gearPosition] = Gear {value};
                        }
                    }
                }
            }
        }

        return std::accumulate(gears.begin(), gears.end(), 0,
            [](const int sum, const decltype(gears)::value_type& kv)
        {
            return sum + kv.second.GetRatio();
        });
    }

private:
    using MaybeLine = std::optional<std::string_view>;

    class Gear
    {
    public:
        explicit Gear() = default;
        explicit Gear(const int partNumber): part1{partNumber} {}

        [[nodiscard]] int GetRatio() const {return part1 * part2;}

        void AddPart2(const int partNumber)
        {
            if (part2 == 0) part2 = partNumber;
        }
    private:
        int part1{};
        int part2{};
    };

    static bool NextTo(
        int index,
        const MaybeLine& prevLine,
        const MaybeLine& currLine,
        const MaybeLine& nextLine)
    {
        auto isSymbol = [](const std::string_view sv, const int idx)
        {
            if (idx < 0|| idx >= sv.size()) return false;
            const char c = sv[idx];
            return !isdigit(c) && c != '.' && c != 0;
        };

        auto adjacentToSymbol = [&index, &isSymbol](const MaybeLine& maybeLine)
        {
            if (maybeLine.has_value())
            {
                const auto line = maybeLine.value();
                return isSymbol(line, index) || isSymbol(line, index - 1) || isSymbol(line, index + 1);
            }

            return false;
        };

        return adjacentToSymbol(prevLine) || adjacentToSymbol(currLine) || adjacentToSymbol(nextLine);
    }

    static int AdjacentGearPosition(
        const int index, const int lineIndex, const size_t length, const std::vector<std::string>& inputLines)
    {
        auto isGear = [](const std::string_view sv, const int idx)
        {
            if (idx < 0|| idx >= sv.size()) return false;
            const char c = sv[idx];
            return c == '*';
        };

        for (int x = lineIndex - 1; x <= lineIndex + 1; ++x)
        {
            if (auto maybeLine = GetLine(x, inputLines); maybeLine.has_value())
            {
                for (int y = index - 1; y <= index + 1; ++y)
                {
                    if (const auto line = maybeLine.value(); isGear(line, y))
                    {
                        // gear position is width * row + col
                        return static_cast<int>(length) * x + y;
                    }
                }
            }
        }

        return -1;
    }

    static MaybeLine GetLine(const int index, const std::vector<std::string>& lines)
    {
        if (index < 0|| index >= lines.size())
        {
            return std::nullopt;
        }

        std::string_view line_view {lines[index]};

        return line_view.empty() ? std::nullopt : std::optional {line_view};
    }

    static std::pair<int, int> ExtractNumberAndLastPosition(const int fromIndex, const std::string_view line)
    {
        // Find the start of the number
        size_t start = fromIndex;
        while (start > 0 && std::isdigit(line[start - 1])) {
            --start;
        }

        // Find the end of the number (one past the last digit)
        size_t end = fromIndex + 1;
        while (end < line.size() && std::isdigit(line[end])) {
            ++end;
        }

        int number {};
        std::from_chars(line.data() + start, line.data() + end, number);
        // Extract and return the number as a string
        return {number, end};
    }
};


int main()
{
    Day03().Run(4361, 467835);
}

