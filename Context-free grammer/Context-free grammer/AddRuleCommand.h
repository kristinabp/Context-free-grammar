#pragma once
#include "ICommand.h"
#include "GrammarSet.h"
class AddRuleCommand :
	public ICommand
{
private:
	GrammarSet& receiver;
public:
	AddRuleCommand(GrammarSet& receiver);

	void execute();
	void unexecute();

	std::string toString();
};

