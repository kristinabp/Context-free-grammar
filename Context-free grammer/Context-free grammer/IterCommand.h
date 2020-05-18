#ifndef ITERCOMMAND_H
#define ITERCOMMAND_H

#include "GrammarSet.h"
#include "ICommand.h"

class IterCommand :
	public ICommand
{
private:
	GrammarSet& receiver;

public:
	IterCommand(GrammarSet& receiver);

	void execute();
	void unexecute();

	std::string toString();
};
#endif // !ITERCOMMAND_H