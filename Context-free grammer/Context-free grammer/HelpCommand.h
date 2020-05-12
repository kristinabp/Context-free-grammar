#pragma once
#include "ICommand.h"
#include "GrammarSet.h"
class HelpCommand :
	public ICommand
{
private:
	GrammarSet& receiver;

public:
	HelpCommand(GrammarSet& receiver);

	void execute();
	void unexecute();

	std::string toString();
};

