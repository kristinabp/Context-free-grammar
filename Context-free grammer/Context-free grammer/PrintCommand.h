#pragma once
#include "ICommand.h"
#include "GrammarSet.h"
class PrintCommand :
	public ICommand
{
private:
	GrammarSet& receiver;
public:
	PrintCommand(GrammarSet& receiver);

	void execute();
	void unexecute();

	std::string toString();
};

