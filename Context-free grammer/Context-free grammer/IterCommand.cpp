#include "IterCommand.h"

IterCommand::IterCommand(GrammarSet & receiver):receiver(receiver)
{
}

void IterCommand::execute()
{
	receiver.iter(parameters[1]);
}

void IterCommand::unexecute()
{
}

std::string IterCommand::toString()
{
	return "iter";
}
