#include "aoc/day04_lib.h"

#include <iostream>
#include <sstream>
#include <cstddef>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <numeric>
#include <functional>

using namespace day04lib;

namespace {

class Bingo
{
public:
    typedef std::vector<int> RandomNumbers;

    typedef struct BoardSpot {
        BoardSpot() : 
            value(0), marked(false)
        {            
        }
        BoardSpot(int v) :
            value(v), marked(false)
        {
            
        }
        void mark()
        {
            marked = true;
        }

        int value;
        bool marked;
    } BoardSpot;

    typedef std::vector<BoardSpot> BoardSpots;

    typedef struct Board {
        Board() :
            spots(5*5)
        {
        }

        void mark(int v)
        {
            (void)v;
        }

        std::tuple<bool, BoardSpots> check() const
        {
            bool winner{false};
            BoardSpots spots;

            return std::tuple<bool, BoardSpots>(winner, spots);
        }

        bool is_ready() const
        {
            return std::none_of(spots.cbegin(), spots.cend(), [](BoardSpot s){ return s.value == 0; });
        }

        std::vector<BoardSpot> spots;
    } Board;

    typedef std::vector<Board> Boards;


    Bingo()
    {
    }

    Bingo( RandomNumbers rs, Boards bs ):
        randos(rs), boards(bs)
    {

    }

    ~Bingo()
    {
    }

    void add_board(Board board)
    {
        boards.push_back(board);
    }

    std::tuple<bool, int, BoardSpots> play_round()
    {
        bool has_winner{false};
        BoardSpots winning_spots;
        int last_rando{0};

        has_winner = true;
        return std::tuple<bool, int, BoardSpots>(has_winner, last_rando, winning_spots);
    }

protected:
    RandomNumbers randos;
    Boards boards; 
    Board winner;
};

Bingo::RandomNumbers parse_randos(const std::string& line)
{
    Bingo::RandomNumbers randos;

    std::istringstream stream(line);

    for(;;)
    {
        if (stream.eof())
        {
            break;
        }

        int d;
        char c;

        stream >> d >> c;

        randos.push_back(d);
    }

    return randos;
}

Bingo::Board parse_board(std::istream& data_stream)
{
    Bingo::Board board;
    std::string line;

    for(;;)
    {
        while(std::getline(data_stream, line) && ! line.empty() )
        {
        }

        if (data_stream.eof())
        {
            break;
        }

        for (auto i = 0; i < 5; ++i)
        {
            std::getline(data_stream, line);
            if (data_stream.eof())
            {
                break;
            }

            std::istringstream row_stream(line);
            for (auto v = 0; v < 5; ++v)
            {
                int value;
                row_stream >> value;
                Bingo::BoardSpot spot(value);
                board.spots.push_back(spot);
            }

            if (data_stream.eof())
            {
                break;
            }
        }
    }


    return board;
    
}

Bingo parse_datastream(std::istream& data_stream)
{
    Bingo bingo;

    std::string line;

    std::getline(data_stream, line);
    auto randos = parse_randos(line);
    
    for(;;)
    {
        auto board = parse_board(data_stream);
        if (board.is_ready())
        {
            bingo.add_board(board);
        }

        if (data_stream.eof())
        {
            break;
        }
    }

    return bingo;
}

}

std::size_t day04lib::part1_solve(std::istream& data_stream)
{
    auto bingo = parse_datastream(data_stream);
    Bingo::BoardSpots winning_spots;
    int last_rando{0};
    bool winner{false};
    do 
    {
        auto [winner, last_rando, winning_spots] = bingo.play_round();
    } while(!winner);


    return last_rando * std::accumulate(winning_spots.begin(), winning_spots.end(), 0, 
                                            [](int t, const Bingo::BoardSpot& s){ return t + s.value;}
                                        );
}

std::size_t day04lib::part2_solve(std::istream& data_stream)
{
    auto things = parse_datastream(data_stream);
    return 0;
}
