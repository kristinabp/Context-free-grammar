#pragma once
#include "ICommand.h"
#include "GrammarSet.h"
class SaveCommand :
	public ICommand
{
private:
	GrammarSet& receiver;
public:
	SaveCommand(GrammarSet& receiver);

	void execute();
	void unexecute();

	std::string toString();
};

