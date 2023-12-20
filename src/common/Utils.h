//
// Created by luisdt on 12/20/23.
//
#ifndef UTILS_H
#define UTILS_H

#include <string_view>

#include "boost/algorithm/string.hpp"

template <template <typename...> class Container = std::vector, typename T>
          requires (std::convertible_to<T, std::string_view>)
Container<T> SplitString(T text, char delimiter)
{
    Container<T> stringParts;
    boost::split(stringParts, text,
        [&delimiter](const char c) { return c == delimiter;}, boost::token_compress_on);
    return stringParts;
}

template <template <typename...> class Container = std::vector, typename T, typename PredicateT>
          requires std::convertible_to<T, std::string_view> &&
              std::invocable<PredicateT, char> &&
              std::convertible_to<std::invoke_result_t<PredicateT, char>, bool>
Container<T> SplitString(T text, PredicateT predicate)
{
    Container<T> stringParts;
    boost::split(stringParts, text, predicate, boost::token_compress_on);
    return stringParts;
}

#endif //UTILS_H
