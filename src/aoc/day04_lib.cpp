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
    typedef struct RandomNumbers {
        RandomNumbers(): next(0)
        {
        }

        int get_next()
        {
            if (next >= randos.size())
                return -1;
            return randos[next++];
        }

        std::vector<int> randos;
        size_t next;
    } RandomNumbers;

    typedef struct BoardSpot {
        BoardSpot() :
            value(-1), marked(false)
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
        Board()
        {
        }

        bool mark(int v)
        {
            auto x = std::find_if(std::begin(spots), std::end(spots), [v](BoardSpot s){return s.value == v;});
            if ( x != std::end(spots) )
            {
                x->mark();
                return true;
            }
            return false;
        }

        bool check() const
        {
            for (auto x = std::begin(spots); x != std::end(spots); x += 5)
            {
                if (std::all_of(x, x + 5, [](BoardSpot s){return s.marked;}))
                {
                    return true;
                }
            }

            for (auto x=0; x < 5; ++x)
            {
                BoardSpots column_spots{
                     spots[x],
                     spots[x+5],
                     spots[x+10],
                     spots[x+15],
                     spots[x+20]
                };

                if (std::all_of(std::begin(column_spots), std::end(column_spots), [](BoardSpot s){return s.marked;}))
                {
                    return true;
                }
            }

            return false;
        }

        bool is_ready() const
        {
            return spots.size() == 5*5 &&
                   std::none_of(spots.cbegin(), spots.cend(),
                                    [](BoardSpot s){ return s.value == -1; }
                               )
                    ;
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

    void set_randos(RandomNumbers r)
    {
        randos = r;
    }

    void add_board(Board board)
    {
        boards.push_back(board);
    }

    int playable_boards() const
    {
        return std::accumulate(boards.begin(), boards.end(), 0,
                                        [](auto t, const Board& b){ return b.check() ? t : t+1;}
                                    );

    }
    std::tuple<bool, int, Board> play_round()
    {
        auto last_rando = randos.get_next();
        Board winning_board;
        bool has_winner{false};

        if (last_rando == -1)
        {
            return std::tuple<bool, int, Board>(false, last_rando, Board());
        }

        for (auto &b : boards)
        {
            if (b.check()) //ignore boards that are already complete
                continue;

            if ( b.mark(last_rando) && b.check())
            {
                has_winner = true;
                winning_board = b;
            }
        }

        return std::tuple<bool, int, Board>(has_winner, last_rando, winning_board);
    }

protected:
    RandomNumbers randos;
    Boards boards;
};

// std::ostream & operator<<(std::ostream &os, const Bingo& bingo)
// {
//     os << "Randos: ";
//     for ( auto r : bingo.randos.randos)
//     {
//         os << r << ",";
//     }
//     os << std::endl;

//     os << std::endl;

//     for (auto b : bingo.boards)
//     {
//         for (auto s : b.spots)
//         {
//             os << s.value;
//             if (s.marked)
//                 os << "!";
//             os << " ";
//         }
//         os << std::endl;
//     }
//     os << std::endl;
//     return os;
// }


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

        randos.randos.push_back(d);
    }

    return randos;
}

Bingo::Board parse_board(std::istream& data_stream)
{
    Bingo::Board board;
    std::string line;

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
    std::getline(data_stream, line); //eat the blank

    return board;

}


Bingo parse_datastream(std::istream& data_stream)
{
    Bingo bingo;

    std::string line;

    std::getline(data_stream, line);
    auto randos = parse_randos(line);
    bingo.set_randos(randos);

    std::getline(data_stream, line);    //eat the blank

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

    Bingo::Board winning_board;
    bool winner{false};
    int last_rando{-1};

    do
    {
        std::tie(winner, last_rando, winning_board) = bingo.play_round();
        if (last_rando == -1)
            break;
    } while(!winner);

    return last_rando * std::accumulate(winning_board.spots.begin(), winning_board.spots.end(), 0,
                                            [](int t, const Bingo::BoardSpot& s){ return s.marked ? t : t + s.value;}
                                        );
}

std::size_t day04lib::part2_solve(std::istream& data_stream)
{
    auto bingo = parse_datastream(data_stream);

    Bingo::Board winning_board;
    int last_rando{-1};

    for(;;)
    {
        auto [w, r, b] = bingo.play_round();
        if (r == -1)
            break;

        if (w)
        {
            winning_board = b;
            last_rando = r;
        }

        if (bingo.playable_boards() == 0)
        {
            break; //all boards complete
        }

    }

    return last_rando * std::accumulate(winning_board.spots.begin(), winning_board.spots.end(), 0,
                                            [](int t, const Bingo::BoardSpot& s){ return s.marked ? t : t + s.value;}
                                        );

}
