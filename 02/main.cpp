#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <string>

#define THEM them[0]
#define US us[0]

#define ROCK_THEM 'A'
#define ROCK_US 'X'
#define PAPER_THEM 'B'
#define PAPER_US 'Y'
#define SCISSORS_THEM 'C'
#define SCISSORS_US 'Z'

typedef struct
{
    char them;
    char us;
    int win;
} win;

static std::vector<win> winnings = { { ROCK_THEM, ROCK_US, 3 }, {ROCK_THEM, PAPER_US, 6}, {ROCK_THEM, SCISSORS_US, 0},
                                     { PAPER_THEM, ROCK_US, 0 }, {PAPER_THEM, PAPER_US, 3}, {PAPER_THEM, SCISSORS_US, 6},
                                     { SCISSORS_THEM, ROCK_US, 6 }, {SCISSORS_THEM, PAPER_US, 0}, {SCISSORS_THEM, SCISSORS_US, 3} };

void Part1()
{
    int total = 0;
    std::ifstream ifs("input");

    auto fight = [](char them, char us) -> int
    {
        for (const win& w : winnings)
        {
            if (w.them == them && w.us == us)
                return w.win;
        }

        throw("Run out of options");
    };

    try
    {
        do {

            std::string them, us;
            ifs >> them >> us;

            if (them.empty() || us.empty())
                continue;

            int points = fight(THEM, US) + (US - 'X') + 1;

            std::cout << "them:" << them << ", us: " << us << " = " << points << "\n";

            total += points;

        } while (!ifs.eof());

        std::cout << "Total: " << total << "\n";
    }
    catch (const char* err)
    {
        std::cerr << err << "\n";
    }
}

void Part2()
{
    int total = 0;
    std::ifstream ifs("input");

    auto fight = [](char them, int must) -> char
    {
        for (const win& w : winnings)
        {
            if (w.them == them && w.win == must)
                return w.us;
        }

        throw("Run out of options");
    };

    try
    {
        do {

            std::string them, us;
            ifs >> them >> us;

            if (them.empty() || us.empty())
                continue;

            int outcome = (US - 'X') * 3;

            char must = fight(THEM, outcome);

            int points = outcome + (must - 'X') + 1;

            char type[2] = { 0, 0 };
            type[0] = must;

            std::cout << "them:" << them << ", us: " << type << " = " << points << "\n";

            total += points;

        } while (!ifs.eof());

        std::cout << "Total: " << total << "\n";
    }
    catch (const char* err)
    {
        std::cerr << err << "\n";
    }
}

int main()
{
    Part1();
    Part2();
}
