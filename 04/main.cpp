#include <iostream>
#include <fstream>
#include <string>
#include <tuple>

#define INPUT "input"

std::tuple<std::string, std::string> split(const std::string& line)
{
	size_t pos = line.find(',');

	if (pos == std::string::npos)
		throw("No delimiter in line");

	return std::tuple<std::string, std::string>(line.substr(0, pos), line.substr(pos + 1));
}

std::tuple<int, int> range(const std::string& line)
{
	size_t pos = line.find('-');

	if (pos == std::string::npos)
		throw("No delimiter in range");

	return std::tuple<int, int>(atoi(line.substr(0, pos).c_str()), atoi(line.substr(pos + 1).c_str()));
}

bool contains(const std::tuple<int, int>& first, const std::tuple<int, int>& second)
{
	return (
		(std::get<0>(first) <= std::get<0>(second) && std::get<1>(first) >= std::get<1>(second)) ||
		(std::get<0>(second) <= std::get<0>(first) && std::get<1>(second) >= std::get<1>(first))
		);
}

bool overlap(const std::tuple<int, int>& first, const std::tuple<int, int>& second)
{
	return !(std::get<0>(first) > std::get<1>(second) || std::get<0>(second) > std::get<1>(first));
}

void Part1()
{
	int total = 0;
	std::ifstream ifs(INPUT);

	if (!ifs)
		return;

	std::string line;

	try
	{
		while (1)
		{
			ifs >> line;

			if (ifs.eof())
				break;

			auto pairs = split(line);
			if (contains(range(std::get<0>(pairs)), range(std::get<1>(pairs))))
				total++;
		}
	}
	catch (const char* err)
	{
		std::cerr << err << "\n";
		return;
	}

	std::cout << total << "\n";
}

void Part2()
{
	int total = 0;
	std::ifstream ifs(INPUT);

	if (!ifs)
		return;

	std::string line;

	try
	{
		while (1)
		{
			ifs >> line;

			if (ifs.eof())
				break;

			auto pairs = split(line);
			if (overlap(range(std::get<0>(pairs)), range(std::get<1>(pairs))))
				total++;
		}
	}
	catch (const char* err)
	{
		std::cerr << err << "\n";
		return;
	}

	std::cout << total << "\n";
}

int main()
{
	Part1();
	Part2();

	return 0;
}
