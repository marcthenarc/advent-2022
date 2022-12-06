#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

#define INPUT "input.txt"

void extractCrates(const std::string& line, std::vector<std::string>& horizontalCrates)
{
	// Create a compressed grid from strings.
	std::string crates;

	for (size_t i = 0; i < line.size(); i++)
	{
		if (line[i] == '[')
			crates.push_back(line[++i]);
		else if (!(i % 4))
			crates.push_back('.');
	}

	horizontalCrates.push_back(crates);
}

void extractGrid(const std::string& line, std::vector<std::string>& crates, std::vector<std::string>& stacks)
{
	// This only works for single digits.  If grid ever expands larger than 9, this won't work.
	// Grid in this quiz is base-1.  We take the last number for the width of a base-0 vector width.
	size_t width = (size_t)atoi(line.substr(line.find_last_not_of(" ")).c_str());
	stacks.resize(width);

	// Transpose the horizontal crates into vertical stacks
	for (const auto& c : crates)
	{
		for (int i = 0; i < c.size(); i++)
		{
			if (c[i] != '.')
				stacks[i].push_back(c[i]);
		}
	}
}

void extractOrders1(const std::string& line, std::vector<std::string>& stacks)
{
	std::string move, from, to;
	size_t amount, start, end;

	std::istringstream iss(line);
	iss >> move >> amount >> from >> start >> to >> end;

	// Base-0
	--start;
	--end;

	for (size_t i = 0; i < amount; i++)
	{
		stacks[end].insert(stacks[end].begin(), stacks[start][0]);
		stacks[start].erase(stacks[start].begin());
	}
}

void extractOrders2(const std::string& line, std::vector<std::string>& stacks)
{
	std::string move, from, to;
	size_t amount, start, end;

	std::istringstream iss(line);
	iss >> move >> amount >> from >> start >> to >> end;

	// Base-0
	--start;
	--end;

	std::string swap;

	swap.insert(swap.begin(), stacks[start].begin(), stacks[start].begin() + amount);
	stacks[start].erase(stacks[start].begin(), stacks[start].begin() + amount);
	stacks[end].insert(stacks[end].begin(), swap.begin(), swap.end());
}

void extractRows(std::ifstream& ifs, int step)
{
	char buffer[256];
	std::vector<std::string> crates, stacks;

	while (1)
	{
		if (ifs.eof())
			break;

		ifs.getline(buffer, 256);
		std::string line(buffer);

		// [ indicates reading crates and keeping them in a temporary container.
		if (line.find("[") != std::string::npos)
		{
			extractCrates(line, crates);
		}
		// m indicate a move command.  Depending on the step, the command will be extracted - insert as is or copied in block to
		// the beginning of the stack.
		else if (line.find("m") != std::string::npos)
		{
			if (step == 1)
				extractOrders1(line, stacks);
			else
				extractOrders2(line, stacks);
		}
		// A non-empty line indicate the grid line.  That were we pull out the number of stacks
		// and swap the horizontal crates to vertical stacks.
		else if (!line.empty())
		{
			extractGrid(line, crates, stacks);
		}
	}

	for (const auto& c : stacks)
		std::cout << c[0];

	std::cout << "\n";
}

void Part2()
{
	std::ifstream ifs(INPUT);

	try
	{
		if (!ifs)
			throw("Can't open input");

		extractRows(ifs, 2);
	}
	catch (const char* err)
	{
		std::cout << err << "\n";
		return;
	}
}

void Part1()
{
	std::ifstream ifs(INPUT);

	try
	{
		if (!ifs)
			throw("Can't open input");

		extractRows(ifs, 1);
	}
	catch (const char* err)
	{
		std::cout << err << "\n";
		return;
	}
}

int main()
{
	Part1();
	Part2();
}
