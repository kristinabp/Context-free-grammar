#ifndef OPENCOMMAND_H
#define OPENCOMMAND_H

#include "GrammarSet.h"
#include "ICommand.h"

class OpenCommand :
	public ICommand
{
private:
	GrammarSet& receiver;

public:
	OpenCommand(GrammarSet& receiver);

	void execute();
	void unexecute();

	std::string toString();
};
#endif // !OPENCOMMAND_H

