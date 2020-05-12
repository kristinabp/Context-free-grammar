#pragma once
#include "ICommand.h"
#include "GrammarSet.h"
class ListCommand :
	public ICommand
{
private:
	GrammarSet& receiver;
public:
	ListCommand(GrammarSet& receiver);

	void execute();
	void unexecute();

	std::string toString();
};

