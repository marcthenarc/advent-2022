#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

bool my_sort(int a, int b)
{
    return a > b;
}

void Second()
{
    char buffer[10];
    int cumul = 0;
    int most = 0;
    std::vector<int> best = { 0, 0, 0 };

    std::ifstream ifs("input");

    do
    {
        ifs.getline(buffer, 10);

        if (strlen(buffer) == 0)
        {
            auto copy = best;
            copy.push_back(cumul);
            std::sort(copy.begin(), copy.end(), my_sort);
            best = { 0, 0, 0 };
            std::copy(copy.begin(), copy.begin() + 3, best.begin());

            for (int i : best)
                std::cout << i << "\n";

            std::cout << "\n";
           
            cumul = 0;
        }
        else
        {
            cumul += std::atoi(buffer);
        }

    } while (!ifs.eof());

    int sum = 0;

    for (int i : best)
        sum += i;

    std::cout << sum << "\n";
}

void First()
{
    char buffer[10];
    int cumul = 0;
    int most = 0;

    std::ifstream ifs("input");

    do
    {
        ifs.getline(buffer, 10);

        if (strlen(buffer) == 0)
        {
            if (most < cumul)
            {
                most = cumul;
                std::cout << cumul << "\n";
            }

            cumul = 0;
        }
        else
        {
            cumul += std::atoi(buffer);
        }

    } while (!ifs.eof());
}

int main()
{
    First();
    Second();
}

