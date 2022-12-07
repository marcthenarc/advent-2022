#include <iostream>
#include <fstream>
#include <string>

#define INPUT "input"

size_t find_dup(std::string sub)
{
	std::string acc;

	for (size_t i = 0; i < sub.size(); i++)
	{
		size_t found = acc.find(sub[i]);

		if (found == std::string::npos)
		{
			acc.push_back(sub[i]);
		}
		else
		{
			return found + 1;
		}
	}

	return std::string::npos;
}

void Part(int markerLength)
{
	std::ifstream ifs(INPUT);
	std::string markers;
	size_t lowmarker = 0;
	bool found = false;

	try
	{
		if (!ifs)
			throw("Can't open input");

		do
		{
			char c;
			ifs >> c;

			if (ifs.eof())
				break;

			markers.push_back(c);

			if (markers.size() >= markerLength && markers.size() - lowmarker == markerLength)
			{
				size_t index = find_dup(markers.substr(lowmarker, c));

				if (index == std::string::npos)
				{
					found = true;
					break;
				}

				lowmarker += index;
			}

		} while (!found);
	}
	catch (const char* err)
	{
		std::cerr << err << "\n";
		return;
	}

	std::cout << markers.size() << "\n";
}

int main()
{
	Part(4);
	Part(14);
}