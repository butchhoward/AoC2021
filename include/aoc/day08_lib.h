#ifndef DAY08_LIB_H
#define DAY08_LIB_H
#include <iostream>
#include <cstddef>
#include <vector>
#include <map>

namespace day08lib {

typedef struct DigitalDisplay
{
    std::vector<std::string> inputs;
    std::vector<std::string> outputs;

} DigitalDisplay;
typedef std::vector<DigitalDisplay> DigitalDisplays;


std::size_t part1_solve(std::istream& data_stream);
std::size_t part2_solve(std::istream& data_stream);

DigitalDisplays parse_datastream(std::istream& data_stream);

typedef std::map<char,char> Decoder;
Decoder create_decoder(const DigitalDisplay& display);

size_t decode_display(const DigitalDisplay& display);
int decode_output( const std::string& output, const Decoder& decoder);

std::ostream & operator<<(std::ostream &os, const std::vector<std::string>& things);
std::ostream & operator<<(std::ostream &os, const DigitalDisplay& thing);
std::ostream & operator<<(std::ostream &os, const DigitalDisplays& things);
std::ostream & operator<<(std::ostream &os, const Decoder& things);


}
#endif
