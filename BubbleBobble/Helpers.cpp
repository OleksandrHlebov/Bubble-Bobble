#include "Helpers.h"
#include <fstream>
#include <sstream>
#include <cassert>

void dae::ReadLevelLayout(const std::string& path, std::vector<bool>& destination)
{
	std::ifstream layoutFile{ path };
	if (!layoutFile.is_open())
	{
		throw std::runtime_error("failed to open layout file");
	}
	std::string line;
	int index{};
	while (std::getline(layoutFile, line))
	{
		std::stringstream sstream{ line };
		while (std::getline(sstream, line, ';'))
		{
			assert(index < std::ssize(destination));
			destination[index++] = std::stoi(line);
		}
	}
}
