#include "PrintCommand.h"



PrintCommand::PrintCommand(GrammarSet& receiver):receiver(receiver)
{
}

void PrintCommand::execute()
{
	receiver.print(parameters[1]);
}

void PrintCommand::unexecute()
{
}

std::string PrintCommand::toString()
{
	return "print";
}
