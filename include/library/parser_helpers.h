#ifndef PARSER_HELPERS_H_
#define PARSER_HELPERS_H_

#include <vector>
#include <iostream>
#include <string>

namespace parser_helpers {

std::vector<int> parse_comma_ints(std::istream& data_stream);
std::vector<std::string> split(const std::string& pp, char delim=' ');

}
#endif
