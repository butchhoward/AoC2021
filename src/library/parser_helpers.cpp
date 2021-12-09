#include <library/parser_helpers.h>

#include <sstream>
#include <numeric>
#include <ranges>


std::vector<int> parser_helpers::parse_comma_ints(std::istream& data_stream)
{
    std::vector<int> data;

    std::string line;
    for (;std::getline(data_stream, line);)
    {
        std::istringstream parts(line);
        for(;;)
        {
            if (parts.eof())
            {
                break;
            }
            int number;
            parts >> number;
            parts.ignore(std::numeric_limits<std::streamsize>::max(), ',');

            data.push_back(number);
        }
    }

    return data;
}

//from https://www.fluentcpp.com/2019/05/14/3-types-of-macros-that-improve-c-code/
#define FWD(...) ::std::forward<decltype(__VA_ARGS__)>(__VA_ARGS__)

std::vector<std::string> parser_helpers::split(const std::string& pp, char delim)
{
    //this was a deep c++20 hole I fell into...lots of learning here

    //from https://brevzin.github.io/c++/2020/07/06/split-view/
    auto split_strs = [](auto&& pattern){
        return std::ranges::views::split(FWD(pattern))
            | std::ranges::views::transform([](auto p){
                auto c = p | std::ranges::views::common;
                return std::string(c.begin(), c.end());
            });
    };

    auto fields = pp | split_strs(delim);
    auto fields_as_vector = std::vector<std::string>(fields.begin(), fields.end());

    return fields_as_vector;
}
