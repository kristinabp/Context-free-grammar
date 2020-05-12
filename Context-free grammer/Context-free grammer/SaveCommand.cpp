#include "SaveCommand.h"



SaveCommand::SaveCommand(GrammarSet& receiver):receiver(receiver)
{
}

void SaveCommand::execute()
{
	receiver.save(parameters[1], parameters[2]);
}

void SaveCommand::unexecute()
{
}

std::string SaveCommand::toString()
{
	return "save";
}
