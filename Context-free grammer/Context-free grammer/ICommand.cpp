#include "ICommand.h"

void ICommand::addParameters(std::string input)
{
	std::string current;
	int i = 0;
	if (!parameters.empty())
	{
		parameters.clear();
	}

	while (i < input.size())
	{
		while (i < input.size() && input[i] != ' ')
		{
			current.push_back(input[i]);
			i++;
		}
		parameters.push_back(current);
		current.clear();
		i++;
	}
}
