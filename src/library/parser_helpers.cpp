#include <library/parser_helpers.h>

#include <sstream>
#include <numeric>


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
