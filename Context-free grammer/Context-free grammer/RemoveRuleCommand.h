#pragma once
#include "ICommand.h"
#include "GrammarSet.h"

class RemoveRuleCommand :
	public ICommand
{
private:
	GrammarSet& receiver;
public:
	RemoveRuleCommand(GrammarSet& receiver);

	void execute();
	void unexecute();

	std::string toString();
	
};

