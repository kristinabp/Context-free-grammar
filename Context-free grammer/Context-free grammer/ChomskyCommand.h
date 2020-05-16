#ifndef CHOMSKYCOMMAND_H
#define CHOMSKYCOMMAND_H
#include "GrammarSet.h"
#include "ICommand.h"

class ChomskyCommand:
	public ICommand
{
private:
	GrammarSet& receiver;

public:
	ChomskyCommand(GrammarSet& receiver);

	void execute();
	void unexecute();

	std::string toString();
};
#endif // !CHOMSKYCOMMAND_H

