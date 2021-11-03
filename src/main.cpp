#include "day01.h"
#include "day01.h"
#include "day01.h"
#include "day01.h"
#include "day01.h"
#include "day01.h"
#include "day01.h"
//MAKEMODULE INCLUDE MARKER. DO NOT DELETE


#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <ctime>
#include <chrono>
#include <functional>
#include <map>

#include <chrono_helpers.h>


typedef std::function<int(const std::string&)> DayFunction;
typedef std::map<int, DayFunction> DaysType;

namespace {

auto datafile(int day)
{
    //dayNN_data.txt
    std::stringstream d;
    d << "./data/day" << std::setfill('0') << std::setw(2) << day << "_data.txt";
    return d.str();
}

void solve_a_day(const DaysType::value_type& day)
{
    auto start = std::chrono::steady_clock::now();

    day.second(datafile(day.first));

    auto end = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "\tTime: " << chrono_helper::format_duration(elapsed) << " " <<  std::endl;
}


}

int main(int argc, char *argv[])
{

    DaysType days = {
         {1, day01}
        ,{01, day01}
    ,{01, day01}
    ,{01, day01}
    ,{01, day01}
    ,{01, day01}
    ,{01, day01}
    ,{01, day01}
    //MAKEMODULE LIST MARKER. DO NOT DELETE
    };

    auto start = std::chrono::steady_clock::now();

    int day_arg(0);
    if (argc == 2)
    {
        std::istringstream stream(argv[1]);
        stream >> day_arg;

        auto one_day = days.find(day_arg);
        if ( one_day == days.end())
        {
            std::cout << "Use a day that exists, probably between 1 and " << days.size() << std::endl;
            return 1;
        }

        solve_a_day(*one_day);
    }
    else
    {
        for ( auto one_day : days)
        {
            solve_a_day(one_day);
        }
    }

    auto end = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Total Time: " << chrono_helper::format_duration(elapsed) << " " <<  std::endl;


    return 0;
}
