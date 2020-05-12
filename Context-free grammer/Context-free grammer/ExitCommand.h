#pragma once
#include "ICommand.h"
#include "GrammarSet.h"
class ExitCommand :
	public ICommand
{
private:
	GrammarSet& receiver;
public:
	ExitCommand(GrammarSet& receiver);
	void execute();
	void unexecute();

	std::string toString();
};

