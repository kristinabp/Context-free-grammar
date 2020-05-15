#include "Validator.h"

bool Validator::validateCommand(ICommand * cmd, std::string input)
{
	std::vector<std::string> words;
	std::string current;
	int i = 0;
	while (i < input.size())
	{
		while (i < input.size() && input[i] != ' ')
		{
			current.push_back(input[i]);
			i++;
		}
		words.push_back(current);
		current = "";
		i++;
	}

	if (words[0] == "open")
	{
		//input --> open filename
		if (words[0] == cmd->toString() && words.size() == 2)
		{
			return true;
		}
		else return false;
	}
	else if (words[0] == "help")
	{
		//input --> help
		if (words[0] == cmd->toString())
		{
			return true;
		}
		else return false;
	}
	else if (words[0] == "exit")
	{
		//input --> exit
		if (words[0] == cmd->toString())
		{
			return true;
		}
		else return false;
	}
	else if (words[0] == "list")
	{
		//input --> list
		if (words[0] == cmd->toString())
		{
			return true;
		}
		else return false;
	}
	else if (words[0] == "print")
	{
		//input --> print id
		if (words[0] == cmd->toString() && words.size()==2)
		{
			return true;
		}
		else return false;
	}
	else if (words[0] == "save")
	{
		//input --> save id filename
		if (words[0] == cmd->toString() && words.size() == 3)
		{
			return true;
		}
		else return false;
	}
	else if (words[0] == "removerule")
	{
		//input --> remuverule id index
		if (words[0] == cmd->toString() && words.size() == 3)
		{
			return true;
		}
		else return false;
	}
	else if (words[0] == "addrule")
	{
		//input --> addrule id rule
		if (words[0] == cmd->toString() && words.size() == 3)
		{
			return true;
		}
		else return false;
	}
	else if (words[0] == "saveas")
	{
		//input --> saveas filename
		if (words[0] == cmd->toString() && words.size() == 2)
		{
			return true;
		}
		else return false;
	}
	else if (words[0] == "close")
	{
		//input --> close
		if (words[0] == cmd->toString())
		{
			return true;
		}
		else return false;
	}
}
