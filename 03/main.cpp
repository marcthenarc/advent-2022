#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

void part2()
{
    std::string first, second, third;
    std::ifstream ifs("input");
    int total = 0;

    try
    {
        if (!ifs)
            throw("Can't open input");

        while (1)
        {
            ifs >> first >> second >> third;

            if (ifs.eof())
                break;

            auto f1 = std::find_if(first.begin(), first.end(), [&](char c1) {

                auto f2 = std::find_if(second.begin(), second.end(), [&](char c2) {

                    auto f3 = std::find_if(third.begin(), third.end(), [&](char c3) {
                        return c2 == c3;
                    });

                    return f3 != third.end() && c1 == c2;
                });

                return f2 != second.end();
            });

            if (f1 == first.end())
                throw("No common type.");

            total += (*f1 > 'a') ? *f1 - 'a' + 1 : *f1 - 'A' + 27;
        }

        std::cout << total << "\n";
    }
    catch (const char *err)
    {
        std::cerr << err << "\n";
    }
}

void part1()
{
    std::string line;
    std::ifstream ifs("input");
    int total = 0;

    try
    {
        if (!ifs)
            throw("Can't open input");

        while (1)
        {
            ifs >> line;
    
            if (ifs.eof())
                break;

            size_t half = line.size() / 2;
    
            std::string first = line.substr(0, half);
            std::string second = line.substr(half);

            auto f1 = std::find_if(first.begin(), first.end(), [second](char c1) {

                auto f2 = std::find_if(second.begin(), second.end(), [c1](char c2) {
                    return c1 == c2;
                });

                return f2 != second.end();
            });

            if (f1 == first.end())
                throw("No common type.");

            total += (*f1 > 'a') ? *f1 - 'a' + 1 : *f1 - 'A' + 27;
        }

        std::cout << total << "\n";
    }
    catch (const char *err)
    {
        std::cerr << err << "\n";
    }
}

int main()
{
    part1();
    part2();

    return 0;
}
