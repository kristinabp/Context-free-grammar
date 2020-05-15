#ifndef CLOSECOMMAND_H
#define CLOSECOMMAND_H

#include "ICommand.h"
#include "GrammarSet.h"

class CloseCommand:
	public ICommand
{
private:
	GrammarSet& receiver;

public:
	CloseCommand(GrammarSet& receiver);

	void execute();
	void unexecute();

	std::string toString();
};
#endif // !CLOSECOMMAND_H

