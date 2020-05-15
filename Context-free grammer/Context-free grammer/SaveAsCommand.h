#ifndef SAVEASCOMMAND_H
#define SAVEASCOMMAND_H

#include "ICommand.h"
#include "GrammarSet.h"

class SaveAsCommand :
	public ICommand
{
private:
	GrammarSet& receiver;

public:
	SaveAsCommand(GrammarSet& receiver);

	void execute();
	void unexecute();

	std::string toString();
};
#endif // !SAVEASCOMMAND_H

