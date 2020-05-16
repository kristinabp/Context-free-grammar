#include "ChomskyCommand.h"

ChomskyCommand::ChomskyCommand(GrammarSet & receiver):receiver(receiver)
{
}

void ChomskyCommand::execute()
{
	receiver.chomsky(parameters[1]);
}

void ChomskyCommand::unexecute()
{
}

std::string ChomskyCommand::toString()
{
	return "chomsky";
}
