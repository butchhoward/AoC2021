
#include "chrono_helpers.h"

#include <ctime>
#include <sstream>
#include <iomanip>



std::string chrono_helper::format_duration(std::chrono::microseconds timeInMicroSec)
{
    auto c(timeInMicroSec.count());
    std::ostringstream oss;
    oss << std::setfill('0') 
        << (c % 1000000000) / 1000000
        << "."
        << std::setw(3)
        << (c % 1000000) / 1000
        << ","
        << std::setw(3)
        << c % 1000;
    return oss.str();
}
